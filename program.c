
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>


pthread_mutex_t rw_mutex;
pthread_mutex_t mutex;

int read_count=0;
int data=5;

void *writer(void *arg)
{

do
{
	pthread_mutex_lock(&rw_mutex);
	printf("Writer writing data...\n");
	data=data+10;
	printf("Writed data:%d\n",data);
	pthread_mutex_unlock(&rw_mutex);
}while(1);

}

void *reader(void *arg1)
{
do
{
	pthread_mutex_lock(&mutex);
	read_count++;

	if(read_count==1)
	{
		pthread_mutex_lock(&rw_mutex);
	}
	pthread_mutex_unlock(&mutex);

	printf("Reader reading data...\n");
	printf("Readed data:%d\n",data);

	pthread_mutex_lock(&mutex);
	read_count--;
	if(read_count==0)
	{
		pthread_mutex_unlock(&rw_mutex);
	}
	pthread_mutex_unlock(&mutex);
}while(1);
}

int main()
{

}
