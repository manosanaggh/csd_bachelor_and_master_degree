#include <stdio.h>

int main()
{
    int N, lnsz = 1, i, j, k, l;

    printf("Please give N:");
    scanf("%d", &N);

    if(N >= 0)
    {
    for (i = N; i > 0; i--)
    {
        for (l = (i-1); l > 0; l--)
        {
            printf(" ");
        }
        for (j = 0; j < lnsz; j++)
        {
            if (j > 0)
            {
                printf("/");
            }
        }

        printf("A");

        for(k = 0; k < lnsz; k++)
        {
            if (k > 0)
            {
                printf("\\");
            }
        }
        printf("\n");
        lnsz++;
    }

    lnsz--;

    for (i = 0; i < N; i++)
    {
        for (l = 0; l < i; l++)
        {
        printf(" ");
        }
        for (j = lnsz; j > 0; j--)
        {
            if (j < lnsz)
            {
            printf("\\");
            }
        }

        printf("V");

        for(k = lnsz; k > 0; k--)
        {
            if (k < lnsz)
            {
                printf("/");
            }
        }
        printf("\n");
        lnsz--;
    }
    }



    return 0;
}
