WITH
    cte_value_of_pizzeria_orders AS (
        SELECT pizzeria.name, count(*) AS count1, 'order' AS action_type
        FROM person_order
        JOIN menu ON person_order.menu_id = menu.id
        JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
        GROUP BY pizzeria.name
    ),
    cte_value_of_pizzeria_visits AS (
        SELECT pizzeria.name, count(*) AS count2, 'visit' AS action_type
        FROM person_visits
        JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
        GROUP BY pizzeria.name
    )
SELECT name, COALESCE(count1, 0) + COALESCE(count2, 0) AS total_count
FROM cte_value_of_pizzeria_orders
FULL JOIN cte_value_of_pizzeria_visits USING (name)
ORDER BY total_count DESC, name