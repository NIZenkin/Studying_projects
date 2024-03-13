#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

void main()
{
    int sockfd, newsockfd1, newsockfd2;

    int clilen1, clilen2;

    int n;
    char line[1000];

    struct sockaddr_in servaddr, cliaddr1, cliaddr2;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Ошибка в функции socket");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(51000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    {
        perror("Ошибка в функции bind");
        close(sockfd);
        exit(1);
    }

    if(listen(sockfd, 5) < 0)
    {
        perror("Ошибка в функции listen");
        close(sockfd);
        exit(1);
    }

    if((newsockfd2 = accept(sockfd, (struct sockaddr *)&cliaddr2, &clilen2)) < 0)
    {
        perror("Ошибка в функции accept");
        close(sockfd);
        exit(1);
    }

    while(1)
    {
        clilen1 = sizeof(cliaddr1);
        clilen2 = sizeof(cliaddr2);
         
        if((newsockfd1 = accept(sockfd, (struct sockaddr *)&cliaddr1, &clilen1)) < 0)
        {
            perror("Ошибка в функции accept");
            close(sockfd);
            close(newsockfd2); // Закрываем соединение, если возникла ошибка
            exit(1);
        }

        while((n = read(newsockfd1, line, 999)) > 0)
        {
            if((n = write(newsockfd1, line, strlen(line) + 1)) < 0)
            {
                perror("Ошибка в функции write");
                close(sockfd);
                close(newsockfd1); // Закрываем оба соединения при ошибке
                close(newsockfd2);
                exit(1);
            }

            if((n = write(newsockfd2, line, strlen(line) + 1)) < 0)
            {
                perror("Ошибка в функции write");
                close(sockfd);
                close(newsockfd1); // Закрываем оба соединения при ошибке
                close(newsockfd2);
                exit(1);
            }
        } 

        if(n < 0)
        {
            perror("Ошибка в функции read");
            close(sockfd);
            close(newsockfd1); // Закрываем оба соединения при ошибке
            close(newsockfd2);
            exit(1);
        }

        // Закрываем дескриптор присоединенного сокета и уходим ожидать нового соединения
        close(newsockfd1);
    }
}