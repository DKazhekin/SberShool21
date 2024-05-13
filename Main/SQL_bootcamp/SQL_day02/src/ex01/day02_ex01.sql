WITH missing_date AS (
    SELECT ('2022-01-01'::DATE + day) AS missing_date
    FROM GENERATE_SERIES(0, 9, 1) AS day
),

visits_12_people AS (
    SELECT visit_date FROM person_visits
    WHERE person_id = 1 OR person_id = 2
)

SELECT missing_date FROM missing_date
LEFT JOIN visits_12_people ON missing_date.missing_date = visits_12_people.visit_date
WHERE visit_date IS Null
ORDER BY missing_date