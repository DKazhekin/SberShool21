WITH pizzas AS (
    SELECT pizza_name, pizzeria_id, price FROM menu
    WHERE pizza_name = 'pepperoni pizza' OR pizza_name = 'mushroom pizza'
)

SELECT pizza_name, name, price FROM pizzas
INNER JOIN pizzeria ON pizzas.pizzeria_id = pizzeria.id
ORDER BY pizza_name, name