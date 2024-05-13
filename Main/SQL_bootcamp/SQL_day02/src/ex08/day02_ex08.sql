WITH rightCities AS (
    SELECT id FROM person
    WHERE (gender = 'male') AND (address = 'Moscow' OR address = 'Samara')
),

rightPizzas AS (
    SELECT id FROM menu
    WHERE pizza_name = 'pepperoni pizza' OR pizza_name = 'mushroom pizza'
)

SELECT DISTINCT name FROM person_order
JOIN person ON person.id = person_order.person_id
WHERE person_id IN (SELECT id FROM rightCities) AND person_id IN (SELECT id FROM rightPizzas)
ORDER BY name DESC