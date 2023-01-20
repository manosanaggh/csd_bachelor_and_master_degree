#include <stdio.h>
#define MAXN 100

int main(int argc, char * argv[])
{
int i, j, N, A[MAXN][MAXN], B[10000], B2[10000], sumR[100], sumC[100], sumMD = 0, sumSD = 0, m = 0, un = 0, k, x, y, c = 0;

if (strcmp(argv[1], "-check") == 0)
{
scanf ("%d",&N);

for(i = 0; i < N; i++)
{
for(j = 0; j < N; j++)
{
 scanf("%d",&A[i][j]);
}
}

for (i = 0; i < N; i++)
{
    sumR[i] = 0;
}

for (i = 0; i < N; i++)
{
    sumC[i] = 0;
}

for (i = 0; i < N; i++)
{
    for (j = 0; j < N; j++)
    {
        sumR[i] += A[i][j];
        sumC[j] += A[i][j];

        if (i == j)
        {
            sumMD += A[i][j];
        }

        if (i + j == N - 1)
        {
            sumSD += A[i][j];
        }
    }
}

for(i = 0; i < N; i++)
{
        if(sumR[i] == ((N*((N*N)+1))/2))
        {
        printf("ROW %d YES\n", i+1);
        m++;
        }
        else
        {
        printf("ROW %d NO\n", i+1);
        }
}

for (i = 0; i < N; i++)
{
        if(sumC[i] == ((N*((N*N)+1))/2))
        {
            printf("COLUMN %d YES\n", i+1);
            m++;
        }
        else
        {
            printf("COLUMN %d NO\n", i+1);
        }
}

if(sumMD == ((N*((N*N)+1))/2))
{
    printf("DIAG1 YES\n");
    m++;
}
else
{
    printf("DIAG1 NO\n");
}

if (sumSD == ((N*((N*N)+1))/2))
{
    printf("DIAG2 YES\n");
    m++;
}
else
{
    printf("DIAG2 NO\n");
}

for(i = 0; i < N; i++)
{
    for(j = 0; j < N; j++)
    {
        B[c] = A[i][j];
        c++;
    }
}

for (i = 0; i < N*N; i++)
{
    B2[i] = B[i];
}

for(i = 0; i < N*N; i++)
{
    for(j = 0; j < N*N; j++)
    {
        if (B[i] != B2[j])
        {
            un++;
        }
    }
}

if (un == (N*N*N*N)-(N*N) && N != 1)
{
    printf("UNIQUE YES\n");
}
else if(N == 1 && A[0][0] == ((N*((N*N)+1))/2))
{
    printf("UNIQUE YES\n");
}
else if (N == 1 && A[0][0] != ((N*((N*N)+1))/2))
{
    printf("UNIQUE NO\n");
}
else
{
    printf("UNIQUE NO\n");
}

if (un == (N*N*N*N)-(N*N) && m == ((2*N)+2))
{
    printf("MAGIC YES\n");
}
else
{
    printf("MAGIC NO\n");
}
}








if (strcmp(argv[1], "-create") == 0)
{
N = atoi(argv[2]);
for(i = 0; i < N; i++)
{
    for(j = 0; j < N; j++)
    {
        A[i][j] = 0;
    }
}

i = N-1;
j = N/2;

x = i;
y = j;

for(k = 1; k <= N*N; k++)
{
    if (A[i][j] == 0)
    {
    A[i][j] = k;
    }

    i++;
    j++;

    if(i == N)
    {
        i = 0;
    }

    if(j == N)
    {
        j = 0;
    }

    if (A[i][j] != 0)
    {
        i = x;
        j = y;
        i--;
    }

    x = i;
    y = j;
}

printf("%d\n", N);

for (i = 0; i < N; i++)
{
    for (j = 0; j < N; j++)
    {
        printf("%d ", A[i][j]);
    }
    printf("\n");
}
}

return 0;
}
