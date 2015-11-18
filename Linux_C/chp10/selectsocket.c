#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 5555    
#define QUEUE_LENGTH 5     
#define BUF_SIZE 200

int main(void)
{
    int server_socket, new_socket;  
    struct sockaddr_in server_addr;    
    struct sockaddr_in client_addr; 
    socklen_t sin_size;
	int client_socket[QUEUE_LENGTH];    
	int conn_num;    
    int yes = 1;
    char buf[BUF_SIZE];
    int ret;
    int i;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
        perror("socket");
        return 0;
    }

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	{
        perror("setsockopt");
        return 0;
    }
    
    server_addr.sin_family = AF_INET;         
    server_addr.sin_port = htons(SERVER_PORT);     
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) 
	{
        perror("bind");
        return 0;
    }

    if (listen(server_socket, 5) == -1) {
        perror("listen");
        return 0;
    }

    printf("listen port %d\n", SERVER_PORT);

    fd_set clientfdset;
    int maxsock;
    struct timeval tv;

    conn_num = 0;
    sin_size = sizeof(client_addr);
    maxsock = server_socket;
    while (1)
	{
        // initialize file descriptor set
        FD_ZERO(&clientfdset);
        FD_SET(server_socket, &clientfdset);

        // timeout setting
        tv.tv_sec = 15;
        tv.tv_usec = 0;

        // add active connection to fd set
        for (i = 0; i < QUEUE_LENGTH; i++) 
		{
            if (client_socket[i] != 0) 
			{
                FD_SET(client_socket[i], &clientfdset);
            }
        }

        ret = select(maxsock + 1, &clientfdset, NULL, NULL, &tv);
        if (ret < 0)
		{
            perror("select");
            break;
        }
		else if (ret == 0)
		{
            printf("waitting timeout\n");
            continue;
        }

        // check every fd in the set
        for (i = 0; i < conn_num; i++) 
		{
            if (FD_ISSET(client_socket[i], &clientfdset)) 
			{
                ret = recv(client_socket[i], buf, sizeof(buf), 0);
                if (ret <= 0) 
				{        
                    printf("client[%d] close\n", i);
                    close(client_socket[i]);
                    FD_CLR(client_socket[i], &clientfdset);
                    client_socket[i] = 0;
                } 
				else
				{     
                    printf("Client[%d] msg:%s\n", i, buf);
					send(client_socket[i], buf, sizeof(buf), 0);
                }
            }
        }

        if (FD_ISSET(server_socket, &clientfdset)) 
		{
            new_socket = accept(server_socket, (struct sockaddr *)&client_addr, &sin_size);
            if (new_socket <= 0)
			{
                perror("accept");
                continue;
            }

            if (conn_num < QUEUE_LENGTH)
			{
                client_socket[conn_num++] = new_socket;
                printf("new client[%d] %s:%d\n", conn_num,
                        inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                if (new_socket > maxsock)
                    maxsock = new_socket;
            }
            else 
			{
                send(new_socket, "sorry overload!", sizeof("sorry overload!"), 0);
                close(new_socket);
                break;
            }
        }
    }

    
    for (i = 0; i < QUEUE_LENGTH; i++) 
	{
        if (client_socket[i] != 0) 
		{
            close(client_socket[i]);
        }
    }

}


