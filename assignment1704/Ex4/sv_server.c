#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(atoi(argv[1]));

    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)))
    {
        perror("bind() failed");
        return 1;        
    }

    if (listen(listener, 5))
    {
        perror("listen() failed");
        return 1;
    }

    printf("Khoi tao server thanh cong!\n");

    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    int client = accept(listener, 
        (struct sockaddr *)&client_addr, 
        &client_addr_len);

    printf("Accepted socket %d from IP: %s:%d\n", 
        client,
        inet_ntoa(client_addr.sin_addr),
        ntohs(client_addr.sin_port));


    // Khai bao ten file
    char *log_file = argv[2];

    // Mo file de ghi thong tin client gui
    FILE *f = fopen(log_file,"a");

    // Tao string luu thong tin client gui
    char buf[1024];    
    memset(buf,0,1024);

    int ret;
    
    while (1){
        ret = recv(client, buf, 1024, 0);
        if (ret <= 0){
            break;
        }
        
        if (ret < sizeof(buf)){
            buf[ret] = 0;
        }

        if(strncmp(buf, "N", 1) == 0){
            break;
        }

        // Tao bien lay thoi gian
        time_t current_time = time(NULL);
        char *formated_time = ctime(&current_time);
        formated_time[strlen(formated_time) - 1] = '\0';

        // Thong tin client gui
        printf("%s %s %s", inet_ntoa(client_addr.sin_addr), formated_time, buf);
        fprintf(f, "%s %s %s", inet_ntoa(client_addr.sin_addr), formated_time, buf);
        
        printf("Saved\n");
    }
    
    fclose(f);

    close(client);
    close(listener);
}