CREATE UNIQUE INDEX IF NOT EXISTS idx_person_discounts_unique ON person_discounts (person_id, pizzeria_id);

SET enable_seqscan TO OFF;
EXPLAIN ANALYZE
INSERT INTO person_discounts(id, person_id, pizzeria_id, discount)
    (SELECT id+19, person_id, pizzeria_id, discount FROM person_discounts LIMIT 1)
