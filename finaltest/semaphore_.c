#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void * read(void * arg);
void * accu(void * arg);
static sem_t sem_one; // 세마포어 1의 주소 값
static sem_t sem_two; // 세마포어 2의 주소 값
static int num;

int main(int argc, char *argv[])
{
    pthread_t id_t1, id_t2;
    
    // 세마포어 두 개를 만들고, 세 번째 매개변수에 각각 0, 1을 넣어서 각각 0, 1로 초기화시킨다.
    sem_init(&sem_one, 0, 0); // 세마포어 1번을 0으로 설정 > 0일 경우, 블로킹 상태 
                              // - 블로킹 상태란? 모든 소켓이 블록이 되는 경우를 뜻함. 따라서, 블록상태의 처리가 진행 되기 전까지 아무것도 수행할 수 없는 상태이다.
    sem_init(&sem_two, 0, 1); // 세마포어 2번을 1로 설정 > 1일 경우, 블로킹 해제 상태

    pthread_create(&id_t1, NULL, read, NULL); // 쓰레드 1번 실행
    pthread_create(&id_t2, NULL, accu, NULL); // 쓰레드 2번 실행

    pthread_join(id_t1, NULL); // 쓰레드 1번이 끝날 때까지 프로세스 대기상태
    pthread_join(id_t2, NULL); // 쓰레드 2번이 끝날 때까지 프로세스 대기상태

    sem_destroy(&sem_one); // 세마포어 1번 종료
    sem_destroy(&sem_two); // 세마포어 2번 종료
    return 0;
}

void * read(void * arg) // 값을 읽어들이는 함수
{
    int i;
    for(i=0; i<5; i++)
    {
        fputs("Input num: ", stdout);

        sem_wait(&sem_two); // 세마포어 2번의 값을 0으로 블로킹하며, num을 쓰레드 2번의 임계영역에 넣는다.
        scanf("%d", &num); // num값을 정상적으로 읽은 뒤에 세마포어 1번의 블로킹을 해제한다.
        sem_post(&sem_one); // num값을 정상적으로 읽은 후에 세마포어 1번의 값을 1로 하여 블로킹을 해제한다.
    }
    return NULL;
}
void * accu(void * arg)
{
    int sum=0, i;
    for(i=0; i<5; i++)
    {
        sem_wait(&sem_one); // 세마포어 1번을 블로킹하여 Num값이 정상적으로 넘어오는지를 확인하며, num을 쓰레드 1번의 임계영역에 넣는다.
        sum+=num;
        sem_post(&sem_two); // sum에 값이 정상적으로 들어간 후, 세마포어 2번의 블로킹을 해제한다.
    }
    printf("Result: %d \n", sum);
    return NULL;
}