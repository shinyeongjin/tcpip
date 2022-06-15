#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <pthread.h>

void* thread_main(void *arg);

int main(int argc, char *argv[])
{
    pthread_t t_id; // 생성할 쓰레드의 ID로 저장할 변수
    int thread_param=5; // 4번째 인자로 전달

/* thread_main 함수의 호출을 시작으로 별도의 실행흐름을 구성하는 쓰레드의 생성을 요청하며
   thread_main 함수호출 시 인자로 변수 thread_param의 주소 값을 전달한다. */
    if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param)!=0)
    {
        puts("pthread_create() error");
        return -1;
    };

    sleep(10); // 프로세스의 종료를 늦추기 위해 사용하며, 프로세스의 종료는 그 안에서 생성된 쓰레드의 종료로 이어진다.
               // 쓰레드의 실행을 보장하기 위해 사용
    puts("end of main");
    
    return 0;
}
void* thread_main(void *arg) // 쓰레드 생성시 바로 실행된다.
{
    int i;
    int cnt=*((int*)arg); // 5회 실행
    for(i=0; i<cnt; i++) 
    {
    sleep(1);
    puts("running thread");
    }
    return NULL;
}