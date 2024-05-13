CREATE UNIQUE INDEX IF NOT EXISTS idx_menu_index
ON menu(pizzeria_id, pizza_name);

INSERT INTO menu
VALUES
(21, 1, 'cheese pizza', 1000)
