WITH person_kate (id, name) AS (
    SELECT id, name
    FROM person
    WHERE name = 'Kate'
)
SELECT menu.pizza_name, menu.price, pizzeria.name AS pizzeria_name, person_visits.visit_date AS visit_date
FROM pizzeria
INNER JOIN menu ON pizzeria.id = menu.pizzeria_id
INNER JOIN person_visits ON menu.pizzeria_id = person_visits.pizzeria_id
INNER JOIN person_kate ON person_visits.person_id = person_kate.id
WHERE menu.price BETWEEN 800 AND 1000
ORDER BY menu.pizza_name, menu.price, pizzeria.name;
