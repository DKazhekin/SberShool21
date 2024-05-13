WITH cte_volume_for_each_person_and_type(user_id, type, volume) AS (
    SELECT balance.user_id, balance.type, SUM(balance.money)
    FROM balance
    GROUP BY balance.user_id, balance.type
),
cte_last_currency_state_for_each_person(currency_id, last_rate_to_usd) AS (
    SELECT DISTINCT balance.currency_id, COALESCE(MAX(currency.rate_to_usd), '1')
    FROM "balance"
    LEFT JOIN currency ON currency.id = balance.currency_id
    GROUP BY balance.currency_id
)
SELECT DISTINCT COALESCE("user".name, 'not defined') AS name,
       COALESCE("user".lastname, 'not defined') AS lastname,
       balance.type AS type,
       cte_volume_for_each_person_and_type.volume AS volume,
       COALESCE(currency.name, 'not defined') AS currency_name,
       COALESCE(cte_last_currency_state_for_each_person.last_rate_to_usd, 1) AS last_rate_to_usd,
       cte_volume_for_each_person_and_type.volume * last_rate_to_usd AS total_volume_in_usd
FROM balance
LEFT JOIN "user" ON "user".id = balance.user_id
INNER JOIN cte_volume_for_each_person_and_type ON cte_volume_for_each_person_and_type.user_id = balance.user_id
LEFT JOIN cte_last_currency_state_for_each_person ON balance.currency_id = cte_last_currency_state_for_each_person.currency_id
LEFT JOIN currency ON currency.id = balance.currency_id
WHERE cte_volume_for_each_person_and_type.type = balance.type
ORDER BY name DESC, lastname, type;


