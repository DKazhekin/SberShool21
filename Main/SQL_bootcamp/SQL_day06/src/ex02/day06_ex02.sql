SELECT person.name AS name, pizza_name, price, price - price * (discount / 100) AS discount_price, pizzeria.name AS pizzeria_name FROM person_order
JOIN menu ON person_order.menu_id = menu.id
JOIN person ON person_order.person_id = person.id
JOIN person_discounts ON person.id = person_discounts.person_id AND menu.pizzeria_id = person_discounts.pizzeria_id
JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
ORDER BY name, pizza_name