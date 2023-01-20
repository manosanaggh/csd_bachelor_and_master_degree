#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int N;
    char abENC[200] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; /*ena string-idio me char* ab-pinakas apo xaraktires -encrypt*/
    char** s; /*pinakas apo strings*/
    char* l;  /*pinakas xaraktirwn = ena string*/
    char* u; /*pinakas xaraktirwn = ena string*/
    int i,k;
    char cipherDEC[200] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; /*-decrypt*/
    char cipherENC[200]; /*CMD*/
    char abDEC[200] ; /*CMD*/


    if (strcmp(argv[1],"-encrypt") == 0 )
    {
    strcpy(cipherENC,argv[2]);

    scanf("%d",&N);

    s = malloc(N*sizeof(char*));
    l = malloc(N*200*sizeof(char));
    u = malloc(N*200*sizeof(char));

    for(i = 0; i < N; i++)
    {
        s[i] = malloc(200*sizeof(char));
        scanf("%s",s[i]);
        if(N == 1)
        {
            strcpy(l,s[i]);
            strcat(l," ");
            break;
        }
        if(i == 0)
        {
            strcpy(l,s[i]);
            strcat(l," ");
            strcat(l,"\n");
            continue;
        }
        strcat(l,s[i]);
        strcat(l," ");
        strcat(l,"\n");
    }

    for(i = 0; i < strlen(l); i++)
    {
        u[i] = toupper(l[i]);
    }

    for(i = 0; i < strlen(u); i++)
    {

        for(k = 0; k < strlen(abENC); k++)
        {
            if(u[i] == abENC[k])
            {
                u[i] = cipherENC[k];
                break;
           }

            if(u[i] == ' ' || u[i] == '\n')
            {
                continue;
            }

            if(k == strlen(abENC) - 1 && u[i] != abENC[k] && u[i] != ' ' && u[i] != '\n')
            {
                u[i] = '?';
                break;
            }
        }
    }

    for (i = 0; i < strlen(u); i++)
    {
        if(N != 1 && strlen(u)-1 == i)
        {
            break;
        }
        printf("%c",u[i]);
    }
    printf("\n");
    free(s);
    free(l);
    free(u);
    }

if (strcmp(argv[1],"-decrypt") ==0 )
{
    strcpy(abDEC,argv[2]);

    scanf("%d",&N);

    s = malloc(N*sizeof(char*));
    u = malloc(N*200*sizeof(char));

    for(i = 0; i < N; i++)
    {
        s[i] = malloc(200*sizeof(char));
        scanf("%s",s[i]);
        if(N == 1)
        {
            strcpy(u,s[i]);
            strcat(u," ");
            break;
        }
        if(i == 0)
        {
            strcpy(u,s[i]);
            strcat(u," ");
            strcat(u,"\n");
            continue;
        }
        strcat(u,s[i]);
        strcat(u," ");
        strcat(u,"\n");
    }

    for(i = 0; i < strlen(u); i++)
    {

        for(k = 0; k < strlen(abDEC); k++)
        {
            if(u[i] == abDEC[k])
            {
                u[i] = cipherDEC[k];
                break;
           }

            if(u[i] == ' ' || u[i] == '\n')
            {
                continue;
            }

            if(k == strlen(abDEC) - 1 && u[i] != abDEC[k] && u[i] != ' ' && u[i] != '\n')
            {
                u[i] = ' ';
                break;
            }
        }
    }

    for (i = 0; i < strlen(u); i++)
    {
        if(N != 1 && strlen(u)-1 == i)
        {
            break;
        }
        printf("%c",u[i]);
    }
    printf("\n");
    free(s);
    free(u);
    }


return 0;
}
