#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
void* thread_main(void *arg);

/* thread_main 함수를 호출한 후, 별도의 실행흐름을 구성하는 쓰레드의 생성을 요청하며,
   thread_main 함수호출 시 인자로 변수 thread_param의 주소 값을 전달한다. */
int main(int argc, char *argv[])
{
    pthread_t t_id; //  생성하려하는 쓰레드의 ID값을 저장할 변수명
    int thread_param=5; // 4번째 인자로 전달
    void * thr_ret; // thread의 main이 변환되는 값을 저장

    if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param)!=0) // 쓰레드 생성
    {
            puts("pthread_create() error");
            return -1;
    };

    if(pthread_join(t_id, &thr_ret)!=0) // 쓰레드 종료 대기
    {
            puts("pthread_join() error");
            return -1;
    };
    
    printf("Thread return message: %s \n", (char*)thr_ret);
    free(thr_ret); // 쓰레드 종료 시 반환 메세지의 메모리 영역을 해제한다.
    return 0;
}

void* thread_main(void *arg)
{
    int i;
    int cnt=*((int*)arg);
    char * msg=(char *)malloc(sizeof(char)*50);
    strcpy(msg, "Hello, I'am thread~ \n");

    for(i=0; i<cnt; i++) // 5회 반복
    {
        sleep(1); puts("running thread");
    }
    return (void*)msg; // void형으로 변환하여 반환된다.
}