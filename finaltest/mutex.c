#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREAD  100

void * thread_inc(void * arg);
void * thread_des(void * arg);

long long num=0; // long long형은 64비트 정수 자료형이다.
pthread_mutex_t mutex; /* mutex의 참조 값 저장을 위한 전역변수를 선언한다.
                            thread_inc, thread des 두 개의 함수에서 이루어지기 때문에 전역 변수로 선언 */
int main(int argc, char *argv[])
{
    pthread_t thread_id[NUM_THREAD];
    int i;

    pthread_mutex_init(&mutex, NULL); // mutex는 쓰레드의 동시 접근을 허용하지 않겠다는 의미이므로 자물쇠 시스템 생성 (ex_화장실을 사용 할 때, 문을 잠궈놓는 원리)

    for(i=0; i<NUM_THREAD; i++) // 증가함수와 감소함수를 번갈아 가며 실행
    {
        if(i%2) //홀수일경우, thread_inc
            pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
        else //짝수일경우, thread_des
            pthread_create(&(thread_id[i]), NULL, thread_des, NULL);
    }

    for(i=0; i<NUM_THREAD; i++) // 쓰레드 종료 대기
        pthread_join(thread_id[i], NULL);

        printf("result: %lld \n", num);
        pthread_mutex_destroy(&mutex); // 자물쇠 시스템 소멸
        return 0;
}
/*
경우에 따라 임계영역 범위는 다를 수 있다.
*/
void * thread_inc(void * arg)
{
    int i; // lock과 unlock이 각각 1번씩만 실행
    pthread_mutex_lock(&mutex); // 크리티컬 세션에 접근하기 위해 쓰레드 내에서 사용하는 구문
    for(i=0; i<50000000; i++)
        num+=1;
    pthread_mutex_unlock(&mutex); // 크리티컬 세션에서 빠져나오기 위해 쓰레드 내에서 사용하는 구문
    return NULL;
}
void * thread_des(void * arg)
{
    int i; // lock과 unlock이 50000000번 반복실행
    for(i=0; i<50000000; i++)
    {
        pthread_mutex_lock(&mutex); // 크리티컬 세션에 접근하기 위해 쓰레드 내에서 사용하는 구문
        num-=1;
        pthread_mutex_unlock(&mutex); // 크리티컬 세션에서 빠져나오기 위해 쓰레드 내에서 사용하는 구문
    }
    return NULL:
}