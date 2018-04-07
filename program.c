#include<stdio.h>
#include<unistd.h>
#include<pthread.h>


pthread_mutex_t rw_mutex;
pthread_mutex_t mutex;

int read_count=0;
int data=5;

void *writer(void *arg)
{
	pthread_mutex_lock(&rw_mutex);
	
	printf("\nNo. of reader present in WRITER SECTION is/are %d\n",read_count);
	printf("Writer writing data...\n");
	sleep(2);
	data=data+10;
	printf("Writed data:%d\n",data);
	
	pthread_mutex_unlock(&rw_mutex);
}

void *reader(void *arg1)
{
	printf("\nReader trying to read data\n");
	
	pthread_mutex_lock(&mutex);
	
	read_count++;

	if(read_count==1)
	{
		pthread_mutex_lock(&rw_mutex);
	}
	
	pthread_mutex_unlock(&mutex);

	printf("Reader reading data...\n");
	printf("No. of reader present inside READER SECTION is/are %d\n",read_count);
	sleep(3);
	printf("Readed data:%d\n",data);
	pthread_mutex_lock(&mutex);
	
	read_count--;
	
	if(read_count==0)
	{
		pthread_mutex_unlock(&rw_mutex);
	}
	
	pthread_mutex_unlock(&mutex);
}


int main()
{
	pthread_t read[5];
	pthread_t write[5];
	
	pthread_mutex_init(&rw_mutex,NULL);
	pthread_mutex_init(&mutex,NULL);
	
	int i;
	
	for(i=0;i<5;i++)
	{
		pthread_create(&read[i],NULL,&reader,NULL);
		pthread_create(&write[i],NULL,&writer,NULL);
	}
	
	
	for(i=0;i<5;i++)
	{
    	pthread_join(read[i],NULL);
    	pthread_join(write[i],NULL);
	}
}
