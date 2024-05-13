CREATE FUNCTION fnc_persons(pgender TEXT)
    RETURNS SETOF person
    LANGUAGE SQL STABLE
    AS
$$
SELECT * FROM person
    WHERE gender = CASE
    WHEN pgender IN ('male', 'female') THEN pgender
    ELSE 'male'
END;
$$;

SELECT * FROM fnc_persons(pgender := 'male');
SELECT * FROM fnc_persons(pgender:= 'female' );