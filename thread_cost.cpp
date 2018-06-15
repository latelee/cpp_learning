/**
多线程、延时测试
g++ -std=c++11 thread_cost.cpp -lpthread
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <iostream>
#include <thread>

#include "mytimer.h"

using namespace std;

void* fun(void *arg) {
    return NULL;
}

void g() {
}

int main() {
    int j, i;
    pid_t pid;
    pthread_t tid;
    struct timeval tv1, tv2;
    unsigned long long elapse;
    int t1, t2;
    int cnt = 0;
    
    CTimer t;

    for (j = 0; j < 50; j++)
    {
        printf("round #%d\n", j);
        /*
         * create POSIX threads
         */

        t.reset();
        for(i = 0;i < 10000;i++) {
            if(pthread_create(&tid, NULL, fun, NULL)) {
                perror("threads create error..!\n");
                exit(EXIT_FAILURE);
            }
            pthread_join(tid, NULL);
        }
        t1 = t.us();
        printf("times: %d\n", t1);


        t.reset();
        /*
         * create c++11 threads
         */
        for(i = 0;i < 10000;i++) {
            thread mythread(g);
            mythread.join();
        }
        t2 = t.us();
        printf("times: %d\n", t2);
        
        if (t1<=t2) cnt++;
        
        usleep(400*1000);
    }
    
    printf("expect: %d of %d\n", cnt, j);

    return 0;

}