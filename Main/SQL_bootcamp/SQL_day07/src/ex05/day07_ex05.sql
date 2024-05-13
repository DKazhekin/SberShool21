SELECT person.name
FROM person_order
JOIN person ON person_order.person_id = person.id
GROUP BY name
ORDER BY name