#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000

void encrypt(char text[], int key) {
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - offset + key) % 26 + offset;
        }
    }
}

void decrypt(char text[], int key) {
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - offset - key + 26) % 26 + offset;
        }
    }
}

void frequency_analysis(const char decrypted_text[]) {
    int freq[26] = {0};
    int total_letters = 0;

    for (int i = 0; i < strlen(decrypted_text); i++) {
        if (isalpha(decrypted_text[i])) {
            char letter = tolower(decrypted_text[i]);
            freq[letter - 'a']++;
            total_letters++;
        }
    }

    printf("\nLetter Frequency Analysis of the Decrypted Text:\n");
    for (int i = 0; i < 26; i++) {
        printf("%c: %.2f%%\n", 'a' + i, (freq[i] / (float)total_letters) * 100);
    }
}


void brute_force_decrypt_and_analyze(const char encrypted_text[], const char original_text[]) {
    char temp_text[MAX_TEXT_LENGTH];


    for (int key = 1; key <= 25; key++) {
        strcpy(temp_text, encrypted_text);  
        decrypt(temp_text, key);

      
        printf("\nAttempt with Key %d: %s\n", key, temp_text);
       
    }
}

int main() {
    char text[MAX_TEXT_LENGTH];
    int key;
    char decrypt_choice, method_choice;

   
    printf("Enter cipher text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';  

    char original_text[MAX_TEXT_LENGTH];
    strcpy(original_text, text);  

  
    printf("Enter encryption key (1-25): ");
    scanf("%d", &key);

    encrypt(text, key);
    printf("Encrypted text: %s\n", text);

    
    printf("Do you want to decrypt the encrypted text? (Y/N): ");
    scanf(" %c", &decrypt_choice);

    if (decrypt_choice == 'Y' || decrypt_choice == 'y') {
       
        int decrypt_key;
        printf("Enter decryption key (must match encryption key): ");
        scanf("%d", &decrypt_key);
        if (decrypt_key == key) {
            decrypt(text, decrypt_key);
            printf("Decrypted text: %s\n", text);
        } else {
            printf("Error: Decryption key does not match the encryption key.\n");
        }

    } else if (decrypt_choice == 'N' || decrypt_choice == 'n') {
     
        printf("Choose decryption method: (B)rute-force or (L)etter-frequency: ");
        scanf(" %c", &method_choice);

        if (method_choice == 'B' || method_choice == 'b') {
          
          
            brute_force_decrypt_and_analyze(text, original_text);
        } else if (method_choice == 'L' || method_choice == 'l') {
      
            frequency_analysis(original_text);
        } else {
            printf("Invalid choice! Exiting.\n");
        }
    } else {
        printf("Invalid choice! Exiting.\n");
    }

    return 0;
}
