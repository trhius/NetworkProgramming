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
    while(1){
        char mssv[1024], hoten[1024], ngaysinh[1024], gpa[1024];
        memset(mssv, 0, 1024);
        memset(hoten, 0, 1024);
        memset(ngaysinh, 0, 1024);
        memset(gpa, 0, 1024);
        
        printf("Nhap du lieu sinh vien: \n");

        printf("  MSSV: ");
        fgets(mssv, 1024, stdin);
        mssv[strcspn(mssv, "\n")] = 0;
        printf("  Ho ten: ");
        fgets(hoten, 1024, stdin);
        hoten[strcspn(hoten, "\n")] = 0;
        printf("  Ngay sinh: ");
        fgets(ngaysinh, 1024, stdin);
        ngaysinh[strcspn(ngaysinh, "\n")] = 0;
        printf("  GPA: ");
        fgets(gpa, 1024, stdin);
        gpa[strcspn(gpa, "\n")] = 0;

        // Dong goi du lieu
        char buf[4*1024 + 1];
        memset(buf, 0, 4*1024+1);
        sprintf(buf, "%s %s %s %s\n", mssv, hoten, ngaysinh, gpa);

        send(client, buf, strlen(buf), 0);

        printf("Tiep tuc? (Y/N): ");
        fgets(buf, 1024, stdin);
        fflush(stdin);
        if(strncmp(buf, "N", 1) == 0){
            break;
        }
    }

    close(client);
    return 0;
}