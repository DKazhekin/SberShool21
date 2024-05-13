CREATE INDEX IF NOT EXISTS idx_person_name
ON person(UPPER(name));

SET enable_seqscan TO OFF;

EXPLAIN
SELECT * FROM person
WHERE UPPER(name) = 'DENIS';
