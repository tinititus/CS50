#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your name?");  // Prompts user                                                      for their name
    printf("hello, %s \n", name);  // Prints user's name
}
