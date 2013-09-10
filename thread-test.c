#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef void * (*fun)(void *);

int gFlag = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread1(void *);
void *thread2(void *);

pthread_mutex_t count_lock;
pthread_cond_t count_nonzero;
unsigned int count;

void *decrement(void*arg)
{
  while(1)
  {
  pthread_mutex_lock(&count_lock);\
    printf("decrement lock\n");
  if(count == 0)
  {
    printf("count== 0\n");
    // pthread_cond_wait先对mutex解锁，然后让进程等待，当条件满足时被唤醒，从新对mutex加锁进行下面的操作
    pthread_cond_wait(&count_nonzero, &count_lock);
  }
  count--;
  printf("decrement\n");
  pthread_mutex_unlock(&count_lock);
  sleep(1);
  }
}

void *increment(void*arg)
{
  while(1)
  {
    printf("enter increment\n");
  pthread_mutex_lock(&count_lock);
  printf("increment lock\n");
  if (count == 0) {
    pthread_cond_signal(&count_nonzero);
  }
  count++;
  printf("increment\n");
  pthread_mutex_unlock(&count_lock);
  sleep(1);
  }
}

int main()
{
  count = 0;
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, decrement, NULL);
  sleep(1);
  pthread_create(&tid2, NULL, increment, NULL);
  pthread_join(tid1, NULL);
  return 0;
  /*
  pthread_t tid1, tid2;
  int rc1, rc2;
  rc2 = pthread_create(&tid2, NULL, thread2, NULL);
  rc1 = pthread_create(&tid1, NULL, thread1, &tid2);
  pthread_cond_wait(&cond, &mutex);
  pthread_join(tid1, NULL);
  return 0;
  */
}

void *thread1(void *arg)
{
  printf("thread1: %u gFlag: %d\n", (unsigned int)pthread_self(), gFlag);
  pthread_mutex_lock(&mutex);
  if (gFlag == 2) {
    pthread_cond_signal(&cond);
  }
  gFlag = 1;
  pthread_mutex_unlock(&mutex);
  pthread_join(*(pthread_t *)arg, NULL);
  printf("leave thread1\n");
  pthread_exit(0);
}

void *thread2(void *arg)
{
  printf("thread2: %u gFlag: %d\n", (unsigned int)pthread_self(), gFlag);
  pthread_mutex_lock(&mutex);
  if (gFlag == 1) {
    pthread_cond_signal(&cond);
  }
  gFlag = 2;
  pthread_mutex_unlock(&mutex);
  printf("leave thread2\n");
  pthread_exit(0);
} 
