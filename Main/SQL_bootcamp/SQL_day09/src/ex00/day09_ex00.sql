-- Creating person_audit table
CREATE TABLE person_audit(
    created       TIMESTAMP WITH TIME ZONE    NOT NULL    DEFAULT CURRENT_TIMESTAMP,
    type_event    CHAR(1)                     NOT NULL    DEFAULT 'I',
    row_id        bigint                      NOT NULL,
    name          varchar,
    age           integer,
    gender        varchar,
    address       varchar

    constraint ch_type_event check (type_event in ('I', 'D', 'U'))
);

COMMENT ON COLUMN person_audit.created IS 'timestamp when a new event has been created.  Default value is a current timestamp and NOT NULL';
COMMENT ON COLUMN person_audit.type_event IS 'possible values I (insert), D (delete), U (update). Default value is ‘I’. NOT NULL. Add check constraint ch_type_event with possible values ‘I’, ‘U’ and ‘D’';
COMMENT ON COLUMN person_audit.row_id IS 'copy of person.id. NOT NULL';
COMMENT ON COLUMN person_audit.name IS 'copy of person.name (no any constraints)';
COMMENT ON COLUMN person_audit.age IS 'copy of person.age (no any constraints)';
COMMENT ON COLUMN person_audit.gender IS 'copy of person.gender (no any constraints)';
COMMENT ON COLUMN person_audit.address IS 'copy of person.address (no any constraints)';

-- Creating function
CREATE FUNCTION fnc_trg_person_insert_audit()
    RETURNS TRIGGER
    LANGUAGE PLPGSQL
    AS
$$
BEGIN
    INSERT INTO person_audit(row_id, name, age, gender, address)
    VALUES (NEW.id, NEW.name, NEW.age, NEW.gender, NEW.address);
    RETURN NULL;
END
$$;

-- Creating trigger
CREATE TRIGGER trg_person_insert_audit
   AFTER INSERT
   ON person
   FOR EACH ROW
   EXECUTE PROCEDURE fnc_trg_person_insert_audit();


-- Insert section
INSERT INTO person(id, name, age, gender, address)
VALUES (10,'Damir', 22, 'male', 'Irkutsk');
