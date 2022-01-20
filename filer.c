#include <stdio.h>

struct MyStruct
{
    char alter[20];
    char ime[20];
    char lok[20];
} MyStruct;

struct MyStruct tabela[10];

void write_struct()
{
    FILE *file;
    file = fopen("agents.txt", "w");
    for (int i = 0; i < 3; i++)
    {
        printf("Alter ego?:");
        scanf("%s", tabela[i].alter);
        printf("Ime operativca?:");
        scanf("%s", tabela[i].ime);
        printf("Lokacija operativca?:");
        scanf("%s", tabela[i].lok);
        fwrite(&tabela[i], sizeof(MyStruct), 1, file);
    }
    
    fclose(file);
}

int main()
{
    write_struct();
    return 0;
}