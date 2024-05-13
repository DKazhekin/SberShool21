-- CREATE TABLE IF NOT EXISTS tsp_graph (
--     point1 varchar,
--     point2 varchar,
--     cost int);
--
-- INSERT INTO tsp_graph VALUES ('a', 'b', 10);
-- INSERT INTO tsp_graph VALUES ('b', 'a', 10);
-- INSERT INTO tsp_graph VALUES ('a', 'c', 15);
-- INSERT INTO tsp_graph VALUES ('c', 'a', 15);
-- INSERT INTO tsp_graph VALUES ('b', 'c', 35);
-- INSERT INTO tsp_graph VALUES ('c', 'b', 35);
-- INSERT INTO tsp_graph VALUES ('b', 'd', 25);
-- INSERT INTO tsp_graph VALUES ('d', 'b', 25);
-- INSERT INTO tsp_graph VALUES ('c', 'd', 30);
-- INSERT INTO tsp_graph VALUES ('d', 'c', 30);
-- INSERT INTO tsp_graph VALUES ('d', 'a', 20);
-- INSERT INTO tsp_graph VALUES ('a', 'd', 20);




WITH helper AS (

    WITH RECURSIVE path AS (
        SELECT point1 as _from, 0 AS _cost, array['a']::varchar[] AS _nodes
        FROM tsp_graph
        WHERE point1 = 'a'
    UNION
        SELECT DISTINCT tsp_graph.point2, path._cost + tsp_graph.cost, array_append(_nodes, tsp_graph.point2)
        FROM path
        INNER JOIN tsp_graph ON tsp_graph.point1 = path._from
        WHERE array_length(path._nodes, 1) < 5
    )

    SELECT _nodes, _cost FROM path
        WHERE
            array_length(_nodes, 1) = 5
            AND _nodes[1] = 'a'
            AND _nodes[array_length(_nodes, 1)] = 'a'
            AND ARRAY(SELECT unnest(_nodes[2:4]) ORDER BY 1)::varchar[] = ARRAY['b', 'c', 'd']::varchar[]
    )

SELECT _cost AS total_cost, _nodes AS tour FROM helper
WHERE _cost = (SELECT MIN(_cost) FROM helper)

UNION

SELECT _cost AS total_cost, _nodes AS tour FROM helper
WHERE _cost = (SELECT MAX(_cost) FROM helper)

ORDER BY total_cost, tour
