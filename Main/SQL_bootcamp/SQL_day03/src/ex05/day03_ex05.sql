WITH cte_visit_without_ordering(person_id, pizzeria_id, visit_date) AS (SELECT person_visits.person_id,person_visits.pizzeria_id, visit_date
                                                FROM person_visits
                                                         LEFT JOIN person_order ON person_visits.visit_date = person_order.order_date
                                                WHERE person_order.order_date IS NULL)

SELECT pizzeria.name AS pizzeria_name
FROM pizzeria
JOIN cte_visit_without_ordering ON pizzeria.id = cte_visit_without_ordering.pizzeria_id
JOIN person ON cte_visit_without_ordering.person_id = person.id
WHERE person.name = 'Andrey'



