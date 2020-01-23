#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string txt);
int count_words(string txt);
int count_sentences(string txt);

int main(void)
{
    string text = get_string("Text: ");  // Gets input text
    int num_letters = count_letters(text);
    //printf("\n%i letter(s)\n", count_letters(text));
    int num_words = count_words(text);
    //printf("%i word(s)\n", num_words);
    int num_stc = count_sentences(text);
    //printf("%i sentence(s)\n", num_stc);

    float L = ((float) num_letters / num_words) * 100;
    //printf("L: %.2f\n", L);
    float S = ((float) num_stc / num_words) * 100;
    //printf("S: %.2f\n", S);
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string txt)
{
    // Counts how many letters there are in the string
    int letters_num = 0;

    for (int i = 0; txt[i] != '\0'; i++)
    {
        if (isalpha(txt[i]))  // Function isalpha is in 'ctype' library and checks if a character is an alphabetical one
        {
            letters_num++;
        }
    }

    return letters_num;
}

int count_words(string txt)
{
    // Counts how many spaces there are in the string and adds 1 in order to get the number of words in it
    int spaces_num = 0;

    for (int i = 0; txt[i] != '\0'; i++)
    {
        if (isspace(txt[i]))  // Function isspace is in 'ctype' library and checks if a character is equal to space
        {
            spaces_num++;
        }
    }

    return spaces_num + 1;

}

int count_sentences(string txt)
{
    // Counts how many '.', '!' and '?' characters there are in the string in order to find how many words there are in it
    int stc_num = 0;

    for (int i = 0; txt[i] != '\0'; i++)
    {
        if (txt[i] == '.' || txt[i] == '!' || txt[i] == '?')  // Checks if is one of the characters of interest
        {
            stc_num++;
        }
    }

    return stc_num;

}
