#include <stdio.h>

int main ()
{
    int N, i = 2, j, check, counter = 1, k = 0;

    scanf("%d",&N);

while (counter <= N)
{
    while (k <= (N-1))
    {
        check = 1;

        for (j = 2; j < i; j++)
        {
            if (i % j == 0)
            {
               check = 0;
            }

        }

        if (check)
        {
            k++;
            printf("%d\n", i);
        }
        i++;

    }

    counter++;
}

return 0;
}
