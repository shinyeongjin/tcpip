#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
void * thread_summation(void * arg); //sum 하는 함수 

int sum=0;

int main(int argc, char *argv[])
{
	pthread_t id_t1, id_t2;
	int range1[]={1, 5};
	int range2[]={6, 10};
	
	pthread_create(&id_t1, NULL, thread_summation, (void *)range1); //1번 쓰레드 생성 
	pthread_create(&id_t2, NULL, thread_summation, (void *)range2); //2번 쓰레드 생성 
	//쓰레드가 생성되면서 thread_summation 함수가 실행된다.
	pthread_join(id_t1, NULL); //1번 쓰레드 종료될 때까지 프로세스 종료하지 않는다.
	pthread_join(id_t2, NULL); //2번 쓰레드 종료될 때까지 프로세스 종료하지 않는다.
	printf("result: %d \n", sum); //쓰레드1과 2가 전역변수 sum에 접근하기 때문에 문제의 소지 발생
	return 0;
}

void * thread_summation(void * arg) 
{
	int start=((int*)arg)[0];
	int end=((int*)arg)[1];

	while(start<=end)
	{
		sum+=start;
		start++;
	}
	return NULL;
}