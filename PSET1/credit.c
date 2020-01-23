#include <stdio.h>
#include <cs50.h>

int main (void)
{
    long number;
    long number_aux;
    long number_div;
    int counter = 0;
    int sum = 0;
    int counter_aux = 0;
    int sum_aux = 0;
    int total = 0;
    bool visa = false;
    bool maybe_amex = false;
    bool amex = false;
    bool maybe_master = false;
    bool master = false;
        
    number = get_long("Number: ");
    number_aux = number;
    
    while (number_aux >= 1) 
    {
        number_aux /= 10;
        counter += 1;
    }
    //printf("Number of digits: %i\n", counter);
    
    number_aux = number/10;
    
    for (int i = 0; number_aux > 1; i++) 
    {
        if (number_aux < 10 && number_aux == 4) visa = true;
        
        if ((number_aux < 100 && number_aux > 10) && ((number_aux == 7) || (number_aux == 4))) maybe_amex = true;
        if (number_aux < 10 && number_aux == 3 && maybe_amex == true) amex = true;
        
        if ((number_aux < 100 && number_aux > 10) && ((number_aux == 5) || (number_aux == 4) || (number_aux == 3) || (number_aux == 2) || (number_aux == 1))) maybe_master = true;
        if (number_aux < 10 && number_aux == 5 && maybe_master == true) master = true;
        
        //printf("number_aux: %ld\n", number_aux);
        number_div = number_aux % 10;
        number_aux = number_aux/100;
        
        if ((2*number_div >= 10)) 
        {
            sum += 1+(2*number_div-10);
        }
        else 
        {
            sum += 2*number_div;
        }
        //printf("2*number_div: %ld\n", number_div);
        counter_aux++; 
    }
    //printf("sum: %i\n", sum);
    
     number_aux = number;
     for (int i = 0; number_aux > 1; i++) 
    {
        //printf("number_aux: %ld\n", number_aux);
        number_div = number_aux % 10;
        number_aux = number_aux/100;
        sum_aux += number_div;
    }
    
    total = sum + sum_aux;
    printf("total: %i\n", total);
    if (total % 10 == 0) 
    {
        //printf("Maybe it's valid!\n");
        if (counter == 15 && amex == true) 
        {
            printf("AMEX\n");
        }
        else if (counter == 16 && master == true)
        {
            printf("MASTERCARD\n");
        }
        else if ((counter == 13 || counter == 16) && (visa == true))
        {
            printf("VISA\n");
        }
        else 
        {
            printf("INVALID\n");
        }
    }
    else 
    {
        printf("INVALID\n");
    }   
}
