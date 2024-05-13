WITH intersaction AS(
    SELECT order_date AS action_date, person_id AS id FROM person_order
    INTERSECT
    SELECT visit_date, person_id FROM person_visits
)

SELECT action_date, name AS person_name FROM person
JOIN intersaction USING(id)
ORDER BY action_date, person_name DESC