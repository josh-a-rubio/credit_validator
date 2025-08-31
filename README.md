🔑 Credit Card Validator

A C program that validates credit card numbers using a 3-step layered approach:

Sanitation Check → ensures input is the correct length (12–19 digits) and contains only numbers.

Luhn’s Algorithm → verifies the number passes the checksum rule used by real credit cards.

IIN (Issuer Identification Number) Check → identifies the card issuer (Visa, MasterCard, AMEX, Discover, Diners Club, JCB).
