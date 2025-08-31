# 🔑 Credit Card Validator  

A C program that validates credit card numbers using a **3-step layered approach**:  

1. **Sanitation Check** → ensures input is the correct length (12–19 digits) and contains only numbers.  
2. **Luhn’s Algorithm** → verifies the number passes the checksum rule used by real credit cards.  
3. **IIN (Issuer Identification Number) Check** → identifies the card issuer (Visa, MasterCard, AMEX, Discover, Diners Club, JCB).  

---

## 🚀 How to Run  

Clone the repository:

```bash
git clone https://github.com/your-username/credit-card-validator.git
cd credit-card-validator
```
Compile the program:

```bash
gcc credit_validator.c -o credit_validator
```
Run it:

```bash
./credit_validator
```

## 🧪 Example Usage

```bash
Card Number: 4111111111111111
VISA

Card Number: 5500000000000004
MASTERCARD

Card Number: 371449635398431
AMEX

Card Number: 123456789
INVALID
```

## 🛠️ Design Approach

The program is structured in three layers:

1. **Sanitation Check**
   - Input is collected with `fgets()` and validated for length (12–19).
   - Any non-digit character is rejected.
   - Ensures the number is “clean” before further checks.

2. **Luhn’s Algorithm**
   - Doubles every second digit from the right.
   - Adds the digits together.
   - Valid numbers produce a sum divisible by 10.

3. **IIN (Issuer Identification Number) Check**
   - Uses known ranges and lengths to determine the issuer:
     - Visa → starts with 4, length 13/16/19  
     - MasterCard → 51–55 or 2221–2720, length 16  
     - AMEX → 34 or 37, length 15  
     - Discover → 6011, 644–649, or 65, length 16  
     - Diners Club → 36, 38, or 300–305, length 14  
     - JCB → 3528–3589, length 16–19  
   - Prints card type if matched, otherwise outputs `INVALID`.

## 📂 Repository Structure

credit-card-validator/
```
├── credit_validator.c # Main C program
└── README.md # Documentation
```

## 📄 License

This project is licensed under the [MIT License](LICENSE).










