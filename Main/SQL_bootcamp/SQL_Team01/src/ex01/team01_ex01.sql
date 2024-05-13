WITH filtered_df AS
(
    SELECT * FROM balance
    WHERE currency_id IN (SELECT DISTINCT id FROM currency)
),

back_updated AS
(
    SELECT user_id, money, filtered_df.updated, type, currency_id, MAX(currency.updated) AS date FROM filtered_df
    JOIN currency ON filtered_df.currency_id = currency.id
    WHERE filtered_df.updated > currency.updated
    GROUP BY user_id, money, type, currency_id, filtered_df.updated
),

future_updated AS
(
    SELECT user_id, money, filtered_df.updated, type, currency_id, MIN(currency.updated) AS date FROM filtered_df
    JOIN currency ON filtered_df.currency_id = currency.id
    WHERE filtered_df.updated < currency.updated
    GROUP BY user_id, money, type, currency_id, filtered_df.updated
),

back_with_ratio AS
(
    SELECT "user".name AS name, "user".lastname, type, money, back_updated.updated, currency.name AS currency_name, rate_to_usd, date FROM back_updated
    JOIN currency ON back_updated.currency_id = currency.id AND date = currency.updated
    LEFT JOIN "user" ON back_updated.user_id = "user".id
),

future_with_ratio AS
(
    SELECT "user".name AS name, "user".lastname, type, money, future_updated.updated, currency.name AS currency_name, rate_to_usd, date FROM future_updated
    JOIN currency ON future_updated.currency_id = currency.id AND date = currency.updated
    LEFT JOIN "user" ON future_updated.user_id = "user".id
),

union_tables AS

(
    SELECT * FROM back_with_ratio
    UNION
    SELECT * FROM future_with_ratio
),

final_filter AS
(
    SELECT name, lastname, type, money, updated, currency_name, MIN(date) AS date FROM union_tables
    GROUP BY name, lastname, type, money, updated, currency_name
)

SELECT COALESCE(final_filter.name, 'not defined') AS name, COALESCE(lastname, 'not defined'), currency_name, money * rate_to_usd AS currency_in_usd FROM final_filter
JOIN currency ON currency_name = currency.name AND date = currency.updated
ORDER BY name DESC, lastname, currency_name