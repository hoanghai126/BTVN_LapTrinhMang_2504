#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main()
{
    // Khoi tao thu vien
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Tao socket
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Khai bao dia chi server
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8000);

    // Gan cau truc dia chi voi socket
    bind(listener, (SOCKADDR*)&addr, sizeof(addr));

    // Chuyen sang trang thai cho ket noi
    listen(listener, 5);

    // Cho ket noi moi
    SOCKET client = accept(listener, NULL, NULL);



    FILE* f1 = fopen("F:\\Lap trinh mang\\BT tuan 2\\test.txt", "rb");
    char buf[2048];
    int ret;

    ret = fread(buf, 1, sizeof(buf), f1);

    if (ret > 0)
    {
        send(client, buf, ret, 0);
    }

    char msg[256];
    FILE* f = fopen("F:\\Lap trinh mang\\BT tuan 2\\test.txt", "wb");

    while (1)
    {
        int res = recv(client, msg, sizeof(msg), 0);
        if (res <= 0)
        {
            printf("Ket noi khong thanh cong!");
            system("pause");
            return 1;
        }
        if (res < 256) msg[res] = 0;
        printf("Nhan: %s\n", msg);

        fwrite(msg, 1, res, f);
    }

    fclose(f1);
    fclose(f);

    
    closesocket(client);
    closesocket(listener);

    WSACleanup();
}