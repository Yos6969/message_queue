/*
 * @Author: your name
 * @Date: 2022-04-11 17:45:38
 * @LastEditTime: 2022-04-11 17:45:29
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /infoque/main.cpp
 */
/*
 * @Author: your name
 * @Date: 2022-04-11 16:53:48
 * @LastEditTime: 2022-04-11 17:40:07
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /test/main.cpp
 */
#include <iostream>
#include <mqueue.h>
#include <mutex>
#include <chrono>
#include <thread>
#include <string.h>
#define MSG_STOP    "exit"
#define MSESIZE 5
#define CHECK(x) \
    do { \
        if (!(x)) { \
            fprintf(stderr, "%s:%d: ", __func__, __LINE__); \
            perror(#x); \
            exit(-1); \
        } \
    } while (0) \

void Consumer()
{
    int must_stop = 0;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MSESIZE;
    attr.mq_curmsgs = 0;
    mqd_t mq = mq_open("/myQueue_IPC", O_CREAT | O_RDONLY, 0644, &attr);
    if (mq == -1)
    {
        printf("mqueue create failed!\n");
        return;
    }
    else
    {
        printf("mqueue create success!\n");
    }
    char buffer[MSESIZE];
    while(!must_stop)
    {
        ssize_t bytes_read = mq_receive(mq, buffer, MSESIZE, NULL);
        CHECK(bytes_read >= 0);
        buffer[bytes_read] = '\0';
        if (! strncmp(buffer, MSG_STOP, strlen(MSG_STOP)))
        {
            must_stop = 1;
        }
        else
        {
            printf("Received: %s\n", buffer);
        }
    }
    CHECK((mqd_t)-1 != mq_close(mq));
    CHECK((mqd_t)-1 != mq_unlink("/myQueue_IPC"));
}
int main(int, char**) {
    Consumer();
    std::cout << "Hello, world!\n";
}
