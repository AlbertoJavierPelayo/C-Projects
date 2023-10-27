/*rand example: guees the number */

#include <stdlib.h> // srand() rand()
#include <time.h> // system time
#include <iostream>// cout cin

int main()
{
    int secret; // gets random number
    int guess; // user guest
    /* initialize random seed */
    srand(time(NULL));
    // generate a random number between 0 and 10
    secret = (int)(10.0 * ((float)rand() / (float)RAND_MAX));
    do
    {
        std::cout << "Guess the number (0 to 10): \n";
        std::cin >> guess;
        if( secret < guess)
        {
            std::cout << "The secret number is lower \n";
        }else if(secret > guess)
        {
            std::cout << "The secret number is higher \n";
        }
    }while(secret != guess);
    std::cout << "Congratulations \n";
    return 0;
}