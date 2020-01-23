#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do {
    height = get_int("Height: ");  // prompts user for height between 1 and 8
    }
    while (height < 1 || height > 8);
     
    // for loops which print the desired number of spaces and hashes
    for (int line = 0; line < height; line++)
    {
        for (int spaces = height - line; spaces > 1; spaces--) // descrease 1 space each time
        {
            printf(" ");
        }
        
        for (int hashes = 0; hashes <= line; hashes++) // increase 1 hash each time
        {
            printf("#");
        }
        
        printf("  ");
        
        for (int hashes = 0; hashes <= line; hashes++)
        {
            printf("#");
        }
        
        printf("\n");
    }
      
}
