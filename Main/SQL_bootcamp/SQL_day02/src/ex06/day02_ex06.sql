SELECT pizza_name,
       pizzeria.name AS pizzeria_name
FROM menu
         INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
         INNER JOIN person_order ON menu.id = person_order.menu_id
         INNER JOIN person ON person_order.person_id = person.id
WHERE person.name = 'Denis' or person.name = 'Anna'
ORDER BY pizza_name,
         pizzeria_name;