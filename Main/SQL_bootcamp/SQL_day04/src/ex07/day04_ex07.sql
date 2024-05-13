INSERT INTO person_visits(id, person_id, pizzeria_id, visit_date)
VALUES(
       (SELECT max(id)+1 FROM person_visits),
       (SELECT id FROM person WHERE name = 'Dmitriy'),
       (SELECT id FROM pizzeria
                  LEFT JOIN mv_dmitriy_visits_and_eats ON pizzeria.name = mv_dmitriy_visits_and_eats.pizzeria_name
                  WHERE mv_dmitriy_visits_and_eats.pizzeria_name IS NULL LIMIT 1),
       '2022-01-08'
      )