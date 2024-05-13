-- DROP INDEX idx_menu_unique

CREATE INDEX IF NOT EXISTS idx1
ON pizzeria(rating);

SET enable_seqscan TO OFF;

EXPLAIN ANALYSE
SELECT
    menu.pizza_name AS pizza_name,
    max(rating) OVER (PARTITION BY rating ORDER BY rating ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS k
FROM  menu
INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
ORDER BY 1,2
