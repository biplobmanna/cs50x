#include <stdio.h>

#define MAX_DIGITS 20
/** 
 * American Express uses 15-digit numbers, American Express numbers start with 34 or 37
 * MasterCard uses 16-digit numbers,  MasterCard numbers start with 51, 52, 53, 54, or 55
 * Visa uses 13- and 16-digit numbers,  Visa numbers start with 4
 * Find which company the card belongs to
 * @return 0 (for American Express), 1 (for MasterCard), 2 (for VISA), -1 (for invalid)
 * */
int find_card_company(int* digits, int dig_len) {
    if (digits[0] == 4 && (dig_len == 13 || dig_len == 16)){
        printf("VISA\n");
        return 2;
    }
    else if (digits[0] == 5 && \
    (digits[1] == 1 || digits[1] == 2 || digits[1] == 3 || digits[1] == 4 || digits[1] == 5) && \
    dig_len == 16) {
        printf("MASTERCARD");
        return 1;
    }
    else if (digits[0] == 3 && \
    (digits[1] == 4 || digits[1] == 7) && \
    dig_len == 15) {
        printf("American Express");
        return 0;
    }
    else {
        printf("INVALID");
        return -1;
    }
}

/**
 * Find the sum of every other digit in array multiplied by factor
 * starting from last, or last-1
 * @return SUM * factor for all array values at position
 * @param int* array of digits
 * @param int dig_len
 * @param int factor to multiply by
 * @param int start_from last or last - 1
 * */
int find_sum_of_digits(int* digits, int dig_len, int factor, int start_from) {
    int sum = 0;
    int dig_x_2 = 0;
    for(int ix = (dig_len - start_from - 1); ix >= 0; ix -= 2) {
        dig_x_2 = digits[ix] * factor;
        if (dig_x_2 >= 10) 
            // Sum of the digits => 10s place + 1s place
            sum += (dig_x_2 / 10) + (dig_x_2 % 10);
        else
            sum += dig_x_2;
    }
    return sum;
}

/**
 * Find the checksum of the card digits
 * @param int* digits
 * @param int dig_len
 * @return 1: success, -1: failure
 * */
int validate_checksum(int* digits, int dig_len) {
    // Every other digit from last - 1
    // Multiply by 2, and also sum of their digits
    int sum1 = find_sum_of_digits(digits, dig_len, 2, 1);

    // Every other digit from last
    // Only sum of their digits
    int sum2 = find_sum_of_digits(digits, dig_len, 1, 0);

    // sum1 + sum2 must be a multiple of 10
    if ((sum1 + sum2) % 10 == 0)
        return 1;
    else
        return -1;
}

/**
 * Find which card, and validate
 * */
int validate_card(int* digits, int dig_len) {
    // Check which company
    int company = find_card_company(digits, dig_len);
    // If company is invalid
    if (company < 0)
        return -1;
    
    // Validate checksum
    int checksum_validation = validate_checksum(digits, dig_len);
    if (checksum_validation != -1) 
        return company;
    else
        return -1;
}

int find_digits_length(long card_number) {
    int dig_len = 0;
    while (card_number > 0) {
        dig_len++;
        card_number /= 10;
    }
    return dig_len;
}

int* convert_number_to_array(long card_number, int dig_len) {
    static int digits[MAX_DIGITS];

    for(int ix = dig_len - 1; ix >= 0; ix--) {
        digits[ix] = card_number % 10;
        card_number /= 10;
    }
    return digits;
}

void print_card_digits(int* digits, int dig_len) {
    for(int ix = 0; ix < dig_len; ix++) {
        printf("%d, ", digits[ix]);
    }
    printf("\n");
}

int main(void) {
    long card_number;
    printf("card number? : ");
    scanf("%ld", &card_number);
    
    int dig_len = find_digits_length(card_number);
    int* digits = convert_number_to_array(card_number, dig_len);
    
    printf("dig_len: %d\n", dig_len);

    int validated = validate_card(digits, dig_len);
    printf("%d\n", validated);
}