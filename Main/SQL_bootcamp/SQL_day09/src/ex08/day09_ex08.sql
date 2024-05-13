CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop INT DEFAULT 10)
    RETURNS TABLE(fib_number BIGINT)
    LANGUAGE PLPGSQL
    AS
$$
DECLARE
    a BIGINT := 0;
    b BIGINT := 1;
    temp BIGINT;
BEGIN
    IF pstop > 0 THEN
        RETURN NEXT;
        fib_number := a;
    END IF;

    LOOP
        temp := a + b;
        EXIT WHEN temp >= pstop;
        fib_number := temp;
        RETURN NEXT;

        a := b;
        b := temp;
    END LOOP;
    RETURN;
END;
$$;

select * from fnc_fibonacci(100);
select * from fnc_fibonacci();
