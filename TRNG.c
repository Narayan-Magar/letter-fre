#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LFSR function for pseudo-random key generation
void generateKeyStream(int keyStream[], int length, int seed) {
    int lfsr = seed; // Initialize LFSR with a seed value
    int taps = 0b101; // Feedback taps (e.g., positions 3, 1)

    for (int i = 0; i < length; i++) {
        keyStream[i] = lfsr & 1; // Take the last bit as the key stream
        int feedback = 0;

        // XOR selected tap bits
        for (int j = 0; j < 8; j++) {
            if ((taps >> j) & 1) {
                feedback ^= (lfsr >> j) & 1;
            }
        }

        lfsr = (lfsr >> 1) | (feedback << 7); // Shift right and set feedback bit
    }
}

// Function to encrypt the plaintext
void encrypt(const char *plaintext, char *ciphertext, int keyStream[]) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = '0' + ((plaintext[i] - 'A' + keyStream[i]) % 10); // Map A-Z to 0-9
        } else if (plaintext[i] >= '0' && plaintext[i] <= '9') {
            ciphertext[i] = 'A' + ((plaintext[i] - '0' + keyStream[i]) % 26); // Map 0-9 to A-Z
        } else {
            ciphertext[i] = plaintext[i]; // Keep non-alphanumeric characters as is
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; // Null-terminate the ciphertext
}

// Function to decrypt the ciphertext
void decrypt(const char *ciphertext, char *plaintext, int keyStream[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= '0' && ciphertext[i] <= '9') {
            plaintext[i] = 'A' + ((ciphertext[i] - '0' - keyStream[i] + 26) % 26); // Reverse 0-9 to A-Z
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = '0' + ((ciphertext[i] - 'A' - keyStream[i] + 10) % 10); // Reverse A-Z to 0-9
        } else {
            plaintext[i] = ciphertext[i]; // Keep non-alphanumeric characters as is
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate the plaintext
}

int main() {
    char choice;
    char inputText[256], outputText[256];
    int keyStream[256];
    int seed;

    // Input the text to process
    printf("Enter the text: ");
    fgets(inputText, sizeof(inputText), stdin);
    inputText[strcspn(inputText, "\n")] = '\0'; // Remove newline character

    // Ask user for encryption or decryption
    printf("Do you want to (e)ncrypt or (d)ecrypt? ");
    scanf(" %c", &choice);

    // Input the seed for LFSR
    printf("Enter the seed value for LFSR (integer): ");
    scanf("%d", &seed);

    // Generate the key stream
    generateKeyStream(keyStream, strlen(inputText), seed);

    if (choice == 'e' || choice == 'E') {
        // Perform encryption
        encrypt(inputText, outputText, keyStream);
        printf("Encrypted text: %s\n", outputText);
    } else if (choice == 'd' || choice == 'D') {
        // Perform decryption
        decrypt(inputText, outputText, keyStream);
        printf("Decrypted text: %s\n", outputText);
    } else {
        printf("Invalid choice. Exiting.\n");
    }

    return 0;
}
