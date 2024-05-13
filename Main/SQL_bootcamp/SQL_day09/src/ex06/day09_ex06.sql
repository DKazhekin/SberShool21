CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(pperson Text = 'Dmitriy', pprice NUMERIC = 500, pdate DATE = '2022-01-08')
    RETURNS TABLE (pizzeria_name VARCHAR)
    LANGUAGE PLPGSQL
    AS
$$
BEGIN
    RETURN QUERY
        SELECT DISTINCT pizzeria.name FROM person_visits
        JOIN person ON person_visits.person_id = person.id
        JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
        JOIN menu ON pizzeria.id = menu.pizzeria_id
        WHERE person.name = pperson AND menu.price <= pprice AND visit_date = pdate;
END;
$$