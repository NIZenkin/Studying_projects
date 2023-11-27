#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LOGIN 15
#define MAX_LINE 255
#define MAX_FILE 100
#define MAX_NAME 30

int main()
{

    char line[MAX_LINE] = {0};
    char login_arr[MAX_LOGIN] = {0};
    char name[MAX_NAME] = {0};
    char *login = login_arr;
    char *line_p = line;
    char *name_p = name;
    int login_length;
    int colon = 0;
    int iteration = 0; //Защита от бесконечного цикла

    scanf("%s", login);
    login_length = strlen(login);
    FILE *file = fopen("/etc/passwd", "r");

    for(int i = 1; i <= MAX_FILE; i++)
    {
        fgets(line, MAX_LINE, file);

        if(strncmp(login, line, login_length) == 0)
        {
            printf("%s", line);
            break;
        }

        if(i == MAX_FILE)
        {
            printf("login was not found. Exiting...\n");
            return -1;
        }

    }

    while(colon < 4)
    {

        if(strncmp(line_p, ":", 1) == 0)
        {
            colon++;
            line_p++;
            iteration++;
        }
        else
        {
            line_p++;
            iteration++;
        }

        if(iteration >= MAX_LINE)
        {
            printf("Error! Exiting...");
            break;
        }

    }

    iteration = 0;

    while(strncmp(line_p, ":", 1) != 0)
    {
        strncpy(name_p, line_p, 1);
        line_p++;
        name_p++;
        iteration++;

        if(iteration >= MAX_LINE)
            {
                printf("Error! Exiting...");
                break;
            }

    }

    printf("%s", name);
    fclose(file);

    return 0;
}