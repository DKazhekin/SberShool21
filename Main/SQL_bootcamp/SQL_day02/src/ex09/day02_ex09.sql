WITH girls AS
(
    SELECT id AS person_id FROM person
    WHERE gender = 'female'
),

pizzas AS (
    SELECT id FROM menu
    WHERE pizza_name = 'cheese pizza' OR pizza_name = 'pepperoni pizza'
),

answer AS (
    SELECT person_id FROM person_order
    WHERE person_id IN (SELECT * FROM girls) AND menu_id IN (SELECT * FROM pizzas)
    GROUP BY person_id
    HAVING COUNT(DISTINCT menu_id) = 2
)

SELECT name FROM answer
JOIN person ON person.id = answer.person_id
ORDER BY name