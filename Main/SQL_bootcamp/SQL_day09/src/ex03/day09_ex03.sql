-- Creating function
CREATE FUNCTION fnc_trg_person_audit()
    RETURNS TRIGGER
    LANGUAGE PLPGSQL
    AS
$$
BEGIN
    IF TG_OP = 'INSERT' THEN
        INSERT INTO person_audit(type_event, row_id, name, age, gender, address)
        VALUES ('I', NEW.id, NEW.name, NEW.age, NEW.gender, NEW.address);
    ELSIF TG_OP = 'UPDATE' THEN
        INSERT INTO person_audit(type_event, row_id, name, age, gender, address)
        VALUES ('U', OLD.id, OLD.name, OLD.age, OLD.gender, OLD.address);
    ELSE
        INSERT INTO person_audit(type_event, row_id, name, age, gender, address)
        VALUES ('D', OLD.id, OLD.name, OLD.age, OLD.gender, OLD.address);
    END IF;
    RETURN NULL;
END
$$;

-- Creating trigger
CREATE TRIGGER trg_person_audit
   AFTER INSERT OR UPDATE OR DELETE
   ON person
   FOR EACH ROW
   EXECUTE PROCEDURE fnc_trg_person_audit();

INSERT INTO person(id, name, age, gender, address)
VALUES (10,'Damir', 22, 'male', 'Irkutsk');
UPDATE person SET name = 'Bulat' WHERE id = 10;
UPDATE person SET name = 'Damir' WHERE id = 10;
DELETE FROM person WHERE id = 10;
