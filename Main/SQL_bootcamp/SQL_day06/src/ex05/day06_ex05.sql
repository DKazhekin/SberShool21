COMMENT ON TABLE person_discounts IS 'store person discounts';
COMMENT ON COLUMN person_discounts.id IS 'Unique identifier for each discount';
COMMENT ON COLUMN person_discounts.person_id IS 'Identifier of the person associated with the discount';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Identifier of the pizzeria associated with the discount';
COMMENT ON COLUMN person_discounts.discount IS 'Numeric value representing the discount amount';