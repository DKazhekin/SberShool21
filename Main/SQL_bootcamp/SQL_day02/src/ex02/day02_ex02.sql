WITH withinDate AS (
    SELECT person_id, pizzeria_id, visit_date FROM person_visits
    WHERE visit_date BETWEEN '2022-01-01' AND '2022-01-03'
),

visitNnot AS (
    SELECT name, visit_date, pizzeria_id FROM person
    FULL JOIN withinDate ON withinDate.person_id = id
),

finalTable AS (
    SELECT visitNnot.name AS name, visit_date, pizzeria.name AS pizzeria_name FROM visitNnot
    FULL JOIN pizzeria ON pizzeria_id = pizzeria.id
)

SELECT
    CASE
        WHEN name IS NULL THEN '-'
        ELSE name
    END,
    visit_date,
    CASE
        WHEN pizzeria_name IS NULL THEN '-'
        ELSE pizzeria_name
    END
FROM finalTable
ORDER BY name, visit_date, pizzeria_name