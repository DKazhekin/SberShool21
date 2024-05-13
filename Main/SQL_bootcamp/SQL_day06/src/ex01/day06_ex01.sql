WITH cte AS (
    SELECT person_id, pizzeria_id, COUNT(*) AS orders_count
    FROM person_order
    JOIN menu ON person_order.menu_id = menu.id
    GROUP BY person_id, pizzeria_id
)

INSERT INTO person_discounts(id, person_id, pizzeria_id, discount)
(SELECT ROW_NUMBER() OVER () AS id,
       person_id,
       pizzeria_id,
       (CASE
           WHEN orders_count = 1 THEN 10.5
           WHEN orders_count = 2 THEN 22
           ELSE 30
        END)

FROM cte)