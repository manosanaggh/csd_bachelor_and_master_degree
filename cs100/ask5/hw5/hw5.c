#include <stdio.h>
int solve(int row[9],int column[9],int square[3][3],int x,int posi,int posj,int posb,int posc);
int main(int argc,char* argv[])
{
  int A[9][9],B[9],C[9],D[9],E[9],F[9],G[9],H[9],I[9],J[9],TEMP[9],row[9],column[9],S1[3][3],S2[3][3],S3[3][3],S4[3][3],S5[3][3],S6[3][3],S7[3][3],S8[3][3],S9[3][3];
  int i,j,a=0,b=0,c = 0,z = 0,d=0,e=0,f=0,g=0,h=0,k=0,sum = 0,vr = 0,vc = 0,unsolvable = 0, bad=0,posb,posc;

if(strcmp(argv[1],"-check") == 0)
{

for(i = 0; i < 9; i++)
{
for(j = 0; j < 9; j++)
{
 scanf("%d",&A[i][j]);
}
}

for(i = 0; i < 3; i++)
{
    for(j = 0; j < 3; j++)
    {
        B[c] = A[i][j];
        c++;
    }
}

c = 0;
for(i = 0; i < 3; i++)
{
    for(j = 3; j < 6; j++)
    {
        C[c] = A[i][j];
        c++;
    }
}

c = 0;
for(i = 0; i < 3; i++)
{
    for(j = 6; j < 9; j++)
    {
        D[c] = A[i][j];
        c++;
    }
}

c = 0;
for(i = 3; i < 6; i++)
{
    for(j = 0; j < 3; j++)
    {
        E[c] = A[i][j];
        c++;
    }
}

c = 0;
for(i = 3; i < 6; i++)
{
    for(j = 3; j < 6; j++)
    {
        F[c] = A[i][j];
        c++;
    }
}

c = 0;
for(i = 3; i < 6; i++)
{
    for(j = 6; j < 9; j++)
    {
        G[c] = A[i][j];
        c++;
    }
}

c = 0;
for(i = 6; i < 9; i++)
{
    for(j = 0; j < 3; j++)
    {
        H[c] = A[i][j];
        c++;
    }
}

c = 0;
for(i = 6; i < 9; i++)
{
    for(j = 3; j < 6; j++)
    {
        I[c] = A[i][j];
        c++;
    }
}

c = 0;
for(i = 6; i < 9; i++)
{
    for(j = 6; j < 9; j++)
    {
        J[c] = A[i][j];
        c++;
    }
}

c = 0;
for (i = 0; i < 9; i++)
{
    TEMP[i] = B[i];
}

for(i = 0; i < 9; i++)
{
    for(j = 0; j < 9; j++)
    {
        if(B[i] == 0)
        {
            a += 8;
            break;
        }
        if(B[i] != TEMP[j] && B[i] >= 1 && B[i] <= 9)
        {
            a++;
        }
    }
}

for (i = 0; i < 9; i++)
{
    TEMP[i] = C[i];
}

for(i = 0; i < 9; i++)
{
    for(j = 0; j < 9; j++)
    {
        if(C[i] == 0)
        {
           b += 8;
           break;
        }

        if (C[i] != TEMP[j] && C[i] >= 1 && C[i] <= 9)
        {
            b++;
        }
    }
}

for (i = 0; i < 9; i++)
{
    TEMP[i] = D[i];
}

for(i = 0; i < 9; i++)
{
    for(j = 0; j < 9; j++)
    {
        if(D[i] == 0)
        {
           z += 8;
           break;
        }

        if(D[i] != TEMP[j] && D[i] >= 1 && D[i] <= 9)
        {
            z++;
        }
    }
}

for (i = 0; i < 9; i++)
{
    TEMP[i] = E[i];
}

for(i = 0; i < 9; i++)
{
    for(j = 0; j < 9; j++)
    {
        if(E[i] == 0)
        {
           d += 8;
           break;
        }

        if (E[i] != TEMP[j] && E[i] >= 1 && E[i] <= 9)
        {
            d++;
        }

    }
}

for (i = 0; i < 9; i++)
{
    TEMP[i] = F[i];
}

for(i = 0; i < 9; i++)
{
    for(j = 0; j < 9; j++)
    {
        if(F[i] == 0)
        {
           e += 8;
           break;
        }

        if (F[i] != TEMP[j] && F[i] >= 1 && F[i] <= 9)
        {
            e++;
        }

    }
}

for (i = 0; i < 9; i++)
{
    TEMP[i] = G[i];
}

for(i = 0; i < 9; i++)
{
    for(j = 0; j < 9; j++)
    {
        if(G[i] == 0)
        {
           f += 8;
           break;
        }

        if (G[i] != TEMP[j] && G[i] >= 1 && G[i] <= 9)
        {
            f++;
        }

    }
}

for (i = 0; i < 9; i++)
{
    TEMP[i] = H[i];
}

for(i = 0; i < 9; i++)
{
    for(j = 0; j < 9; j++)
    {
        if(H[i] == 0)
        {
           g += 8;
           break;
        }

        if (H[i] != TEMP[j] && H[i] >= 1 && H[i] <= 9)
        {
            g++;
        }

    }
}

for (i = 0; i < 9; i++)
{
    TEMP[i] = I[i];
}

for(i = 0; i < 9; i++)
{
    for(j = 0; j < 9; j++)
    {
        if(I[i] == 0)
        {
           h += 8;
           break;
        }

        if (I[i] != TEMP[j] && I[i] >= 1 && I[i] <= 9)
        {
            h++;
        }

    }
}

for (i = 0; i < 9; i++)
{
    TEMP[i] = J[i];
}

for(i = 0; i < 9; i++)
{
    for(j = 0; j < 9; j++)
    {
        if(J[i] == 0)
        {
           k += 8;
           break;
        }

        if (J[i] != TEMP[j] && J[i] >= 1 && J[i] <= 9)
        {
            k++;
        }

    }
}

for(i = 0; i < 9; i++)
{
    for(c = 0; c < 9; c++)
    {
        B[c] = A[i][c];
    }
    for(j = 0; j < 9; j++)
    {
        if(B[i] == 0)
        {
            sum += 8;
            break;
        }

        if (B[i] != A[i][j] && B[i] >= 1 && B[i] <= 9)
        {
            sum++;
        }
    }
    if(sum != 8 || B[i] < 0 || B[i] > 9)
    {
      printf("Invalid row %d\n",i+1);
    }

    if(sum == 8 && B[i] >= 0 && B[i] <= 9)
    {
      vr++;
    }
    sum = 0;
}

for(j = 0; j < 9; j++)
{
    for(c = 0; c < 9; c++)
    {
        B[c] = A[c][j];
    }
    for(i = 0; i < 9; i++)
    {
        if(B[j] == 0)
        {
            sum += 8;
            break;
        }

        if (B[j] != A[i][j] && B[j] >= 1 && B[j] <= 9)
        {
            sum++;
        }
    }
    if(sum != 8 || B[j] < 0 || B[j] > 9)
    {
      printf("Invalid column %d\n",j+1);
    }

    if(sum == 8 && B[j] >= 0 && B[j] <= 9)
    {
      vc++;
    }
    sum = 0;
}

if(a != 72)
{
   printf("Invalid block 1\n");
}

if(b != 72)
{
   printf("Invalid block 2\n");
}

if(z != 72)
{
   printf("Invalid block 3\n");
}

if(d != 72)
{
   printf("Invalid block 4\n");
}

if(e != 72)
{
   printf("Invalid block 5\n");
}

if(f != 72)
{
   printf("Invalid block 6\n");
}

if(g != 72)
{
   printf("Invalid block 7\n");
}

if(h != 72)
{
   printf("Invalid block 8\n");
}

if(k != 72)
{
   printf("Invalid block 9\n");
}

if(a == 72 && b == 72 && z == 72 && d == 72 && e == 72 && f == 72 && g == 72 && h == 72 && k == 72 && vr == 9 && vc == 9)
{
   printf("OK\n");
}

}

if(strcmp(argv[1],"-solve")==0)
{
for(i = 0; i < 9; i++)
{
for(j = 0; j < 9; j++)
{
scanf("%d",&A[i][j]);
}
}

for(i = 0; i < 3; i++)
{
    for(j = 0; j < 3; j++)
    {
        S1[b][c] = A[i][j];
        c++;

    }
    b++;
}
b = 0;
c = 0;
for(i = 0; i < 3; i++)
{
    for(j = 3; j < 6; j++)
    {
        S2[b][c] = A[i][j];
        c++;
    }
    b++;
}
b = 0;
c = 0;
for(i = 0; i < 3; i++)
{
    for(j = 6; j < 9; j++)
    {
        S3[b][c] = A[i][j];
        c++;
    }
    b++;
}
b = 0;
c = 0;
for(i = 3; i < 6; i++)
{
    for(j = 0; j < 3; j++)
    {
        S4[b][c] = A[i][j];
        c++;
    }
    b++;
}
b = 0;
c = 0;
for(i = 3; i < 6; i++)
{
    for(j = 3; j < 6; j++)
    {
        S5[b][c] = A[i][j];
        c++;
    }
    b++;
}
b = 0;
c = 0;
for(i = 3; i < 6; i++)
{
    for(j = 6; j < 9; j++)
    {
        S6[b][c] = A[i][j];
        c++;
    }
    b++;
}
b = 0;
c = 0;
for(i = 6; i < 9; i++)
{
    for(j = 0; j < 3; j++)
    {
        S7[b][c] = A[i][j];
        c++;
    }
    b++;
}
b = 0;
c = 0;
for(i = 6; i < 9; i++)
{
    for(j = 3; j < 6; j++)
    {
        S8[b][c] = A[i][j];
        c++;
    }
    b++;
}
b = 0;
c = 0;
for(i = 6; i < 9; i++)
{
    for(j = 6; j < 9; j++)
    {
        S9[b][c] = A[i][j];
        c++;
    }
    b++;
}

for(i = 0; i < 9; i++)
{
  for(j = 0; j < 9; j++)
  {
    if(A[i][j]==0)
    {
      for(k = 0; k < 9; k++)
      {
        row[k] = A[i][k];
      }
      for(c = 0; c < 9; c++)
      {
        column[c] = A[c][j];
      }
      if(i >=0 && i < 3 && j >= 0 && j < 3)
      {
          if(i == 0)
          {
            posb=0;
          }
          if(i == 1)
          {
            posb=1;
          }
          if(i == 2)
          {
            posb=2;
          }
          if(j == 0)
          {
            posc=0;
          }
          if(j == 1)
          {
            posc=1;
          }
          if(j == 2)
          {
            posc=2;
          }
          A[i][j]=solve(row,column,S1,1,i,j,posb,posc);
      }
      if(i >=0 && i < 3 && j >= 3 && j < 6)
      {
          if(i == 0)
          {
            posb=0;
          }
          if(i == 1)
          {
            posb=1;
          }
          if(i == 2)
          {
            posb=2;
          }
          if(j == 3)
          {
            posc=0;
          }
          if(j == 4)
          {
            posc=1;
          }
          if(j == 5)
          {
            posc=2;
          }
          A[i][j]=solve(row,column,S2,1,i,j,posb,posc);
      }
      if(i >=0 && i < 3 && j >= 6 && j < 9)
      {
          if(i == 0)
          {
            posb=0;
          }
          if(i == 1)
          {
            posb=1;
          }
          if(i == 2)
          {
            posb=2;
          }
          if(j == 6)
          {
            posc=0;
          }
          if(j == 7)
          {
            posc=1;
          }
          if(j == 8)
          {
            posc=2;
          }
          A[i][j]=solve(row,column,S3,1,i,j,posb,posc);
      }
      if(i >=3 && i < 6 && j >= 0 && j < 3)
      {
          if(i == 3)
          {
            posb=0;
          }
          if(i == 4)
          {
            posb=1;
          }
          if(i == 5)
          {
            posb=2;
          }
          if(j == 0)
          {
            posc=0;
          }
          if(j == 1)
          {
            posc=1;
          }
          if(j == 2)
          {
            posc=2;
          }
          A[i][j]=solve(row,column,S4,1,i,j,posb,posc);
      }
      if(i >=3 && i < 6 && j >= 3 && j < 6)
      {
          if(i == 3)
          {
            posb=0;
          }
          if(i == 4)
          {
            posb=1;
          }
          if(i == 5)
          {
            posb=2;
          }
          if(j == 3)
          {
            posc=0;
          }
          if(j == 4)
          {
            posc=1;
          }
          if(j == 5)
          {
            posc=2;
          }
          A[i][j]=solve(row,column,S5,1,i,j,posb,posc);
      }
      if(i >=3 && i < 6 && j >= 6 && j < 9)
      {
          if(i == 3)
          {
            posb=0;
          }
          if(i == 4)
          {
            posb=1;
          }
          if(i == 5)
          {
            posb=2;
          }
          if(j == 6)
          {
            posc=0;
          }
          if(j == 7)
          {
            posc=1;
          }
          if(j == 8)
          {
            posc=2;
          }
          A[i][j]=solve(row,column,S6,1,i,j,posb,posc);
      }
      if(i >=6 && i < 9 && j >= 0 && j < 3)
      {
          if(i == 6)
          {
            posb=0;
          }
          if(i == 7)
          {
            posb=1;
          }
          if(i == 8)
          {
            posb=2;
          }
          if(j == 0)
          {
            posc=0;
          }
          if(j == 1)
          {
            posc=1;
          }
          if(j == 2)
          {
            posc=2;
          }
          A[i][j]=solve(row,column,S7,1,i,j,posb,posc);
      }
      if(i >=6 && i < 9 && j >= 3 && j < 6)
      {
          if(i == 6)
          {
            posb=0;
          }
          if(i == 7)
          {
            posb=1;
          }
          if(i == 8)
          {
            posb=2;
          }
          if(j == 3)
          {
            posc=0;
          }
          if(j == 4)
          {
            posc=1;
          }
          if(j == 5)
          {
            posc=2;
          }
          A[i][j]=solve(row,column,S8,1,i,j,posb,posc);
      }
      if(i >=6 && i < 9 && j >= 6 && j < 9)
      {
          if(i == 6)
          {
            posb=0;
          }
          if(i == 7)
          {
            posb=1;
          }
          if(i == 8)
          {
            posb=2;
          }
          if(j == 6)
          {
            posc=0;
          }
          if(j == 7)
          {
            posc=1;
          }
          if(j == 8)
          {
            posc=2;
          }
          A[i][j]=solve(row,column,S9,1,i,j,posb,posc);
      }
    }
  }
}

for(i = 0; i < 9; i++)
{
  for(j = 0; j < 9; j++)
  {
    if(A[i][j]==0 || A[i][j]<0 || A[i][j] > 9)
    {
      printf("No solution.\n");
      unsolvable = 1;
      break;
    }
  }
  if(unsolvable==1)
  {
    break;
  }
}


for(i = 0; i < 9; i++)
{
  for(j = 0; j < 9; j++)
  {
    if(A[i][j]==0 || A[i][j]<0 || A[i][j] > 9)
    {
      bad++;
    }
  }
}

if(bad==0)
{
  for(i = 0; i < 9; i++)
  {
    printf(" ");
  for(j = 0; j < 9; j++)
  {
    printf("%d",A[i][j]);
    if(j < 8)
    {
      printf(" ");
    }
  }
  printf("\n");
  }
}

}


return 0;
}

int solve(int row[9],int column[9],int square[3][3],int x,int posi,int posj,int posb,int posc)
{
int solvable = 0,zero = 0,i,j,r=0,c=0,s=0;
for(i = 0; i < 9; i++)
{
  if(row[i] == 0 && posi == i)
  {
    continue;
  }

  if(row[i] == 0)
  {
    r++;
    continue;
  }
  if(row[i] != x && row[i] != 0)
  {
    r++;
  }
}

if(r==8)
{
  solvable++;
}

for(i = 0; i < 9; i++)
{
  if(column[i] == 0 && posj == i)
  {
    continue;
  }

  if(column[i] == 0)
  {
    c++;
    continue;
  }


  if(column[i] != x && column[i] != 0)
  {
    c++;
  }
}

if(c==8)
{
  solvable++;
}

for(i = 0; i < 3; i++)
{
  for(j = 0; j < 3; j++)
  {
  if(square[i][j] == 0 && posb == i && posc == j)
  {
    continue;
  }

  if(square[i][j] == 0)
  {
    s++;
    continue;
  }

  if(square[i][j] != x && square[i][j] != 0)
  {
    s++;
  }
  }
}

if(s==8)
{
  solvable++;
}

if(x>=1 && x<=9)
{
  if(solvable==3)
  {
    return x;
  }
  else
  {
    x++;
    solve(row,column,square,x,posi,posj,posb,posc);
  }
}
else
{
  return 0;
}

}
