#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
struct agent
{
    char alter[20];
    char ime[20];
    char lokacija[20];
} agent;

struct agent tabela[5];
FILE *file;

void nadji(char *buffer, int i)
{
    file = fopen("agents.txt", "r");
    if (file == NULL)
    {
        fprintf(stderr, "\nNemoguc pristup podacima!\n");
    }
    else
    {
        if (strcmp(buffer, tabela[i].alter) == 0)
        {
            printf("Server -> Klijent: %s%s", tabela[i].ime, tabela[i].lokacija);
        }
    }
}*/
char *agents[] = {"ALEKSAVELICKOVICIZRAEL", "TANASIJEIVKOVICNEMACKA", "DUSANPOPOVSRBIJA", "EDWARDSNOWDENAMERIKA", "GORANZIVALJEVICBRITANIJA"};
char *alter[] = {"SPEKTRA", "SHADOW", "JAMESBOND", "WORM", "BIAS"};

int agent(int sock)
{
    char buffer[256], ch;
    int n, i, j, key = 3;

    bzero(buffer, 256);
    n = read(sock, buffer, 255);
    buffer[n] = 0;

    for (i = 0; buffer[i] != '\0'; ++i)
    {
        ch = buffer[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch - key;
            if (ch < 'a')
            {
                ch = ch + 'z' - 'a' + 1;
            }
            buffer[i] = ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = ch - key;
            if (ch < 'A')
            {
                ch = ch + 'Z' - 'A' + 1;
            }
            buffer[i] = ch;
        }
    }

    for (i = 0; i < 5; i++)
    {
        if (strcmp(buffer, alter[i]) == 0)
        {
            printf("Klijent -> Server: %s\n", buffer);
            printf("Server -> Klijent: %s\n", agents[i]);
            return 0;
        }
    }
    printf("Klijent -> Server: %s\n", buffer);
    printf("AlterEgo se ne poklapa, prekidam komunikaciju.\n");
    return 5; // prekidaj program
}

void doprocessing(int sock)
{
    int n, done = 0, j, m, key = 3;
    char buffer[256], sendBuf[256], tempstr[256], ch;
    bzero(buffer, 256);

    while (!done)
    {
        n = read(sock, buffer, 255);
        for (int i = 0; buffer[i] != '\0'; ++i)
        {
            ch = buffer[i];
            if (ch >= 'a' && ch <= 'z')
            {
                ch = ch - key;
                if (ch < 'a')
                {
                    ch = ch + 'z' - 'a' + 1;
                }
                buffer[i] = ch;
            }
            else if (ch >= 'A' && ch <= 'Z')
            {
                ch = ch - key;
                if (ch < 'A')
                {
                    ch = ch + 'Z' - 'A' + 1;
                }
                buffer[i] = ch;
            }
        }
        buffer[n] = 0;

        printf("Klijent -> Server: %s\n", buffer);

        if (strcmp(buffer, "ENDE") == 0)
        {
            done = 1;
            printf("Server -> Klijent: ENDE\n");
        }
        else if (strcmp(buffer, "NEEDINFO") == 0)
        {
            printf("Server -> Klijent: YOUCANGETINFO\n");
            m = agent(sock);
            if (m == 5) // gasi
            {
                done = 1;
            }
        }
        else
        {
            done = 1;
            printf("Netacna komanda, prekidam komunikaciju!\n");
        }
    }
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, clilen, n;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = 5001;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }
    printf("Server started.. waiting for clients ...\n");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1)
    {
        newsockfd = accept(sockfd,
                           (struct sockaddr *)&cli_addr, &clilen);
        printf("Client connected...\n");
        if (newsockfd < 0)
        {
            perror("ERROR on accept");
            exit(1);
        }

        int pid = fork();
        if (pid < 0)
        {
            perror("ERROR on fork");
            exit(1);
        }
        if (pid == 0)
        {
            close(sockfd);
            doprocessing(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    }
}