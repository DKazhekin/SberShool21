CREATE OR REPLACE FUNCTION func_minimum(inp_array ANYARRAY)
    RETURNS INT
    LANGUAGE PLPGSQL
    AS
$$
DECLARE
    element NUMERIC;
    maximum NUMERIC := 1e-300;
BEGIN
    FOREACH element IN ARRAY inp_array
    LOOP
        IF maximum IS NULL OR element > maximum THEN
            maximum := element;
        END IF;
    END LOOP;
    RETURN maximum;
END;
$$;

SELECT func_minimum(VARIADIC inp_array => ARRAY[10.0, -1.0, 5.0, 4.4]);
