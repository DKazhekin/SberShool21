SELECT CONCAT(name, ' (age:', age, ',gender:', QUOTE_LITERAL(gender), ',address:', QUOTE_LITERAL(address), ')') AS person_information FROM person
ORDER BY person_information