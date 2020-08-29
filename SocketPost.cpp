#include <iostream>
#include <winsock2.h>
#include <cstdio>
#include <cstring>
#include <string>

const int BUFSIZE = 2048;
const char* hFormat = "POST %s HTTP/1.1\r\n"
                      "Accept: */*\r\n"
                      "Connection: Keep-Alive\r\n"
                      "Content-Type: application/x-www-form-urlencoded;\r\n"
                      "Content-Length: %d\r\n"
                      "\r\n"
                      "%s";

std::string StartPostRequest(const char* reqUrl, const char* reqBody) {
    WORD wVersionRequest = MAKEWORD(1, 1);
    WSADATA wsa;

    if(WSAStartup(wVersionRequest, &wsa) != 0){
        std::cerr << "初始化套接字库失败" << std::endl;
        exit(0);
    }

    char httpPostRequest[2048] = {0};
    sprintf(httpPostRequest, hFormat, reqUrl, strlen(reqBody), reqBody);

    SOCKET socketClient = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN socketAddr;
    socketAddr.sin_addr.S_un.S_addr = inet_addr("111.202.114.53");
    socketAddr.sin_family = AF_INET;
    socketAddr.sin_port = htons(80);

    if(connect(socketClient, (sockaddr*)&socketAddr, sizeof(socketAddr)) < 0){
        std::cerr << "服务器连接失败" << std::endl;
        exit(0);
    }

    if(send(socketClient, httpPostRequest, strlen(httpPostRequest) + 1, 0) == SOCKET_ERROR){
        std::cerr << "发送失败" << std::endl;
        exit(0);
    }

    std::string s = "";
    int recvLen = 0; char buf[BUFSIZE + 1] = {0};
    while (recvLen = recv(socketClient, buf, BUFSIZE, 0)){
        s += std::string(buf).substr(0, recvLen);
        memset(buf, 0, sizeof(buf));
        if(recvLen != BUFSIZE)  break;
    }

    closesocket(socketClient);
    WSACleanup();

    return s;
}

int main() {
    const char* reqUrl = "http://api.fanyi.baidu.com/api/trans/vip/translate";
    const char* reqBody = "q=卖炭翁，伐薪烧炭南山中。满面尘灰烟火色，两鬓苍苍十指黑。卖炭得钱何所营？身上衣裳口中食。可怜身上衣正单，心忧炭贱愿天寒。夜来城外一尺雪，晓驾炭车辗冰辙。牛困人饥日已高，市南门外泥中歇。翩"
                          "翩两骑来是谁？黄衣使者白衫儿。手把文书口称敕，回车叱牛牵向北。一车炭，千余斤，宫使驱将惜不得。半匹红纱一丈绫，系向牛头充炭直。&from=zh&to=en&appid=20200413000418690&salt=41&sign=e85836dd9656f845687676fae6a55e94";
    std::string recvContent = StartPostRequest(reqUrl, reqBody);
    std::cout << recvContent << std::endl;
}
