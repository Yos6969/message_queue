/*
 * @Author: your name
 * @Date: 2022-04-11 16:29:41
 * @LastEditTime: 2022-04-11 18:06:41
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /infoque/main.cpp
 */
#include <iostream>
#include <mqueue.h>
#include <mutex>
#include <chrono>
#include <thread>
#include <string.h>
#define MSESIZE 5
#define MSG_STOP    "exit"
#define CHECK(x) \
    do { \
        if (!(x)) { \
            fprintf(stderr, "%s:%d: ", __func__, __LINE__); \
            perror(#x); \
            exit(-1); \
        } \
    } while (0) \
    
void Producter()
{
    mqd_t mq;
    mq = mq_open("/myQueue_IPC", O_WRONLY);
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
	while (strncmp(buffer, MSG_STOP, strlen(MSG_STOP)))
	{
		//std::this_thread::sleep_for(std::chrono::seconds(2));
        fgets(buffer, MSESIZE, stdin);
		mq_send(mq, buffer, MSESIZE, 0);   
	}
    CHECK((mqd_t)-1 != mq_close(mq));
}

int main(int, char**) {
    Producter();
}
