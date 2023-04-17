#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    // Khai bao socket
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Khai bao dia chi server
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    // Ket noi den server
    int res = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (res == -1){
        printf("Khong ket noi duoc den server!");
        return 1;
    }

    // Gui tin nhan den server
    char buf[2048];
    while(1){
        printf("Nhap du lieu: ");
        fgets(buf, 2048, stdin);
        if(strncmp(buf, "exit", 4) == 0){
            break;
        }
        send(client, buf, strlen(buf), 0);
    }

    close(client);
    return 0;
}

