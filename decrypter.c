#include <stdio.h>

// Function to encrypt a long variable
long encrypt(long input) {
    // Define a secret key for encryption
    long key = 1234567890;
    // Perform encryption using XOR operation with the key
    return input ^ key;
}

// Function to decrypt a long type encrypted object
long decrypt(long encrypted) {
    // Define the same secret key used for encryption
    long key = 1234567890;
    // Perform decryption using XOR operation with the key
    return encrypted ^ key;
}

int main() {
    long original ;
    scanf("%ld", &original);
    // Encrypt the original variable
    long encrypted = encrypt(original);
    // Decrypt the encrypted variable
    long decrypted = decrypt(encrypted);

    printf("Original: %ld\n", original);
    printf("Encrypted: %ld\n", encrypted);
    printf("Decrypted: %ld\n", decrypted);

    return 0;
}



