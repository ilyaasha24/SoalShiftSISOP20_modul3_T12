#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

int (*mat3)[5];
int row = 0, n, i, j, k;
void* func(void* arg) {
  i = row++;
  for (size_t j = 0; j < 5; j++) {
    n = 0;
    for (k = 1; k < mat3[i][j]; k++) n += k;
    mat3[i][j] += n;
  }
}
int main() {
	key_t key = 3737;
  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  mat3 = shmat(shmid, 0, 0);
  pthread_t tid[4];
  for (i = 0; i < 4; i++) pthread_create(&(tid[i]), NULL, &func, NULL);
  for (i = 0; i < 4; i++) pthread_join(tid[i], NULL);
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 5; j++) {
      printf("%2d ", mat3[i][j]);
		}
		printf("\n");
  }
  shmdt(mat3);
  shmctl(shmid, IPC_RMID, NULL);
}
