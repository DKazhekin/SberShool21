WITH helper AS (
    SELECT person_id as id, order_date FROM person_order
)

SELECT DISTINCT order_date, CONCAT(name, ' (age:', age, ')') AS person_information FROM person
NATURAL JOIN helper
ORDER BY order_date, person_information