#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char* user_input(void);
void validate_checksum(char* card_number);
void validate_IIN(char* card_number);

int main(void)
{
    char* card_number = user_input();
    validate_checksum(card_number);

    return 0;
}

// gets user input . sanitize length and characters
char* user_input(void)
{
    const int min_len = 12;
    const int max_len = 19;
    
    static char card_number[max_len + 2];  
    size_t card_length;
    bool all_digits;
    
    do
    {
        all_digits = true;
        printf("Card Number: ");
        if (!fgets(card_number, sizeof(card_number), stdin))
        {
            card_number[0] = '\0';
        }
        card_length = strlen(card_number);
        
        // Check if input was too long (buffer full but no newline)
        if (card_length == max_len + 1 && card_number[card_length - 1] != '\n')
        {
            int last_char;
            while ((last_char = getchar()) != '\n' && last_char != EOF);  // Clear remaining input
            all_digits = false;
            card_length = 0;
            continue;
        }
        
        if (card_length > 0 && card_number[card_length - 1] == '\n')
        {
            card_number[card_length - 1] = '\0';
            card_length--;
        }
        
        for (size_t i = 0; i < card_length; i++)
        {
            if (card_number[i] < '0' || card_number[i] > '9')
            {
                all_digits = false;
                break;
            }
        }
    
    } while (card_length < min_len || card_length > max_len || !all_digits);
    return card_number;
}

// run luhn's algorithm
void validate_checksum(char* card_number)
{
    int card_length = strlen(card_number);
    int total_sum = 0;
    int product;

    // starting from second to last digit
    for (int i = card_length - 2; i >= 0; i -= 2)
    {
        int digit = card_number[i] - '0';
        product = digit * 2;

        if (product > 9)
        {
            total_sum += (product / 10);
            total_sum += (product % 10);
        }
        else
        {
            total_sum += product;
        }
    }

    // starting from last digit
    for (int i = card_length - 1; i >= 0; i -= 2)
    {
        int digit = card_number[i] - '0';
        total_sum += digit;
    }

    if (total_sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        validate_IIN(card_number);
    }
}

// check IIN
void validate_IIN(char* card_number)
{
    int card_length = strlen(card_number);

    // individual digits
    int first_digit = card_number[0] - '0';
    int second_digit = card_number[1] - '0';
    int third_digit = card_number[2] - '0';
    int fourth_digit = card_number[3] - '0';

    // digits combined
    int first_two_digits = first_digit * 10 + second_digit;
    int first_three_digits = first_digit * 100 + second_digit * 10 + third_digit;
    int first_four_digits = first_digit * 1000 + second_digit * 100 + third_digit * 10 + fourth_digit;

    // visa check
    bool visa_range = first_digit == 4;
    bool visa_length = (card_length == 13) || (card_length == 16) || (card_length == 19);
    bool visa_card = visa_range && visa_length;

    if (visa_card)
    {
        printf("VISA\n");
        return;
    }

    // mastercard check
    bool old_master_range = first_two_digits >= 51 && first_two_digits <= 55;
    bool new_master_range = first_four_digits >= 2221 && first_four_digits <= 2720;
    bool master_length = card_length == 16;
    bool master_card = master_length && (old_master_range || new_master_range);
    
    if (master_card)
    {
        printf("MASTERCARD\n");
        return;
    }

    // amex check
    bool amex_range = first_two_digits == 34 || first_two_digits == 37;
    bool amex_length = card_length == 15;
    bool amex_card = amex_range && amex_length;
    
    if (amex_card)
    {
        printf("AMEX\n");
        return;
    }

    // discover check
    bool discover_range = (first_four_digits == 6011) || 
                            (first_three_digits >= 644 && first_three_digits <= 649) || 
                            (first_two_digits == 65);
    bool discover_length = card_length == 16;
    bool discover_card = discover_range && discover_length;
    
    if (discover_card)
    {
        printf("DISCOVER\n");
        return;
    }

    // diners club check
    bool dinersClub_range = (first_two_digits == 36) || (first_two_digits == 38) ||
                            (first_three_digits >= 300 && first_three_digits <= 305);
    bool dinersClub_length = card_length == 14;
    bool dinersClub_card = dinersClub_range && dinersClub_length;
    
    if (dinersClub_card)
    {
        printf("DINERS CLUB\n");
        return;
    }

    // jcb check
    bool jcb_range = first_four_digits >= 3528 && first_four_digits <= 3589;
    bool jcb_length = card_length >= 16 && card_length <= 19;
    bool jcb_card = jcb_range && jcb_length;
    
    if (jcb_card)
    {
        printf("JCB\n");
        return;
    }

    printf("INVALID\n");
}
