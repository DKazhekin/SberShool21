WITH possible_pizzerias AS (
    SELECT pizzeria_id FROM person_visits
    WHERE visit_date = '2022-01-08' and person_id = 9
),

less_than_800 AS (
    SELECT pizzeria_id FROM menu
    WHERE price < 800
)

SELECT name FROM possible_pizzerias
JOIN pizzeria ON pizzeria.id = possible_pizzerias.pizzeria_id
WHERE id IN (SELECT * FROM less_than_800)