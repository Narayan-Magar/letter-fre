#include <stdio.h>
#include <ctype.h>

#define TOTAL_LETTERS 26

// Approximate English letter frequencies (in percentages)
const double english_freq[TOTAL_LETTERS] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966,
    0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};

void analyze_text(const char *text) {
    int letter_count[TOTAL_LETTERS] = {0}; // To count each letter
    int total_letters = 0;

    // Count each letter in the text
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            int index = tolower(text[i]) - 'a';
            letter_count[index]++;
            total_letters++;
        }
    }

    // Display the table of letter frequencies
    printf("Letter | Cipher Frequency | English Frequency\n");
    printf("-------|------------------|-------------------\n");
    double cipher_freq[TOTAL_LETTERS];
    for (int i = 0; i < TOTAL_LETTERS; i++) {
        cipher_freq[i] = (double)letter_count[i] / total_letters * 100;
        printf("   %c   |      %.2f%%       |      %.2f%%\n", 
               'A' + i, cipher_freq[i], english_freq[i]);
    }

    // Display summary of total results after the table
    printf("\nSummary of Ciphertext Analysis:\n");
    for (int i = 0; i < TOTAL_LETTERS; i++) {
        if (letter_count[i] > 0) {
            printf("Letter '%c': Count = %d, Frequency = %.2f%%\n", 
                   'A' + i, letter_count[i], cipher_freq[i]);
        }
    }
}

int main() {
    char text[1000];

    printf("Enter the ciphertext: ");
    fgets(text, sizeof(text), stdin);

    // Analyze the text
    analyze_text(text);

    return 0;
}
