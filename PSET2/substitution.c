#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)  // argument counter: integer representing number of arguments passed through command line
    {
        // Handles lack of key
        printf("Usage: ./substitution key\n");
        return 1;
    }

    bool alpha = true;
    string key = argv[1];  // argument vector: array which contain arguments passed through command line

    for (int i = 0; i < strlen(key); i++)  // Handles invalid characters in key
    {
        if (isalpha(key[i]) == false)
        {
            alpha = false;
            printf("Key must only contain alphabetic characters\n");
            return 1;
        }
    }

    if (alpha == true && strlen(key) != 26)  // Handles key length
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    else if (alpha == true && strlen(key) == 26)
    {
        int counter = 0;

        for (int i = 0; i < strlen(key); i++)  // Handles duplicate characters
        {
            for (int j = 0; j < strlen(key); j++)
            {
                if (tolower(key[i]) == tolower(key[j]))
                {
                    counter++;
                    if (counter > 26)
                    {
                        printf("Key must not contain repeated characters.");
                        return 1;
                    }
                }
            }
        }

        string plain_text = get_string("plaintext: ");
        string cipher_text = plain_text;

        string alphabet = "abcdefghijklmnopqrstuvwxyz"; // String which we'll use for mapping the key

        for (int i = 0; i < strlen(plain_text); i++)
        {
            for (int j = 0; j < strlen(key); j++)
            {
                if (isupper(plain_text[i]))  // If plaintext character is uppercase, preserve and find corresponding character in the key string
                {
                    if (plain_text[i] == toupper(alphabet[j]))
                    {
                        cipher_text[i] = toupper(key[j]);  // toupper guarantees cipher[i] will be uppercase even if key[j] isn't
                        break;
                    }

                }
                else if (islower(plain_text[i]))  // Same as the above, but for lowercase characters
                {
                    if (plain_text[i] == alphabet[j])
                    {
                        cipher_text[i] = tolower(key[j]);  // tolower guarantees cipher[i] will be lowercase even if key[j] isn't
                        break;
                    }
                }

            }
        }
        printf("ciphertext: %s\n", cipher_text);
        return 0;
    }
}