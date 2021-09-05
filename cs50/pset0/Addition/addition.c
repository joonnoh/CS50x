#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    /*int x = get_int("x: ");
    int y = get_int("y: ");
*/
    srand(time(0));
    int n;
    for (int i = 0; i < 5; i++)
    {
        n = rand() % 3;
        printf("%i\n", n);
    }
}