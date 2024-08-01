# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>

int main() 
{
  sem_t    *a;
  sem_unlink("/philo_a");
  a = sem_open("/philo_a", O_CREAT, S_IRWXU, 5);
  printf("%d\n", (int)a);
  sem_wait(a);
  printf("%d\n", (int)a);
  return 0;

}