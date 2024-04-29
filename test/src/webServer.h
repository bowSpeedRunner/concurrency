#include <iostream>
#include <vector>
#include <unordered_map>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const char * supportHttpMethod = "GET";         // 支持的http方法
const char * supportHttpVersion = "HTTP/1.1";   // 支持的http版本
const char * delimiter = "\r\n";                // http行与行之间的分隔符
const int maxConnectNums = 1024;                // 最大连接数(初始化事件数组)
const int maxBufferNums = 4096;                 // 读写数据时使用的数组大小
const int countTimeInterval = 30;               // 获取当前连接数的间隔时间
const double activeTimeInterval = 60;           // 检查当前连接是否活跃的间隔时间
pthread_mutex_t mutex;
// 记录客户端连接的相关信息
struct fdInfo
{
    time_t lastActiveTime;      // 上次活跃时间
    struct sockaddr_in address; // 客户端连接地址
};
std::unordered_map<int, fdInfo> hash;

// 设置文件描述符为非阻塞
int setfd(int fd);
// 打印当前的连接数目
void * checkConnect(void * arg);
// 检查连接是否活跃
void * getConnectCount(void * arg);
// 请求分析
void http_request(int epfd, int cfd);
// 发送头文件
int sendHeader(int epfd, int cfd, const char * code, const char * msg, const char * fileType, int length);
// 发送响应内容
int sendFile(int epfd, int cfd, const char * fileNmae);
// 获取相应时需要的文件类型
const char * get_mime_type(const char * name);
// 十六进制转十进制
unsigned short hextod(unsigned short hexNums);
// 解决中文乱码
void strdecode(char * to, char * from);