-- Create female function
CREATE FUNCTION fnc_persons_female()
    RETURNS SETOF person
    LANGUAGE SQL STABLE
    AS
$$
SELECT * FROM person
WHERE gender = 'female';
$$;

-- Create male function
CREATE FUNCTION fnc_persons_male()
    RETURNS SETOF person
    LANGUAGE SQL STABLE
    AS
$$
SELECT * FROM person
WHERE gender = 'male';
$$;

SELECT * FROM fnc_persons_female();
SELECT * FROM fnc_persons_male();


