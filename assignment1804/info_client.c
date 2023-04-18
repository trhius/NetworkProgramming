#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_DRIVES 10

int main() {
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000); 

    if (connect(client, (struct sockaddr *)&addr, sizeof(addr))) {
        perror("connect() failed");
        return 1;
    }
        

    //Khoi tao 
    char computer_name[64];
    int num_drives;
    char drives[MAX_DRIVES][2];
    int sizes[MAX_DRIVES];
    int i;

    // Nhập tên máy tính
    printf("Nhap ten may tinh: ");
    scanf("%s", computer_name);

    // Nhập số lượng ổ đĩa và thông tin chi tiết của từng ổ đĩa
    printf("Nhap so luong o dia: ");
    scanf("%d", &num_drives);

    for (i = 0; i < num_drives; i++) {
        printf("Nhap thong tin o dia thu %d:\n", i + 1);
        printf("  Kieu o dia (vd: C): ");
        scanf("%s", drives[i]);
        printf("  Kich thuoc (GB): ");
        scanf("%d", &sizes[i]);
    }


    // Đóng gói dữ liệu và gửi tới info_server
    printf("Ten may tinh %s\nSo o dia %d \n", computer_name, num_drives);
    for (i = 0; i < num_drives; i++) {
        printf("   %s - %dGB", drives[i], sizes[i]);
        if (i < num_drives - 1) {
            printf("\n");
        }
    }

    printf("\n");


    // Ket thuc, dong socket
    close(client);

    return 0;
}
    