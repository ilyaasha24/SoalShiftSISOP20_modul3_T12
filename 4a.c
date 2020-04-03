#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

int mat1[4][2] = {{2,2},{2,2},{2,2},{2,2}};
int mat2[2][5] = {{5,5,5,5,5},{5,5,5,5,5}};
int (*mat3)[5];
int row = 0, i, j, k;
void* mult(void* arg) {
  i = row++;
  for (j = 0; j < 5; j++) for (k = 0; k < 2; k++) mat3[i][j] += mat1[i][k] * mat2[k][j];
}
int main() {
	key_t key = 3737;
  int shmid = shmget(key, sizeof(int[4][5]), IPC_CREAT | 0666);
  mat3 = shmat(shmid, 0, 0);
  pthread_t tid[4];
  for (i = 0; i < 4; i++) pthread_create(&(tid[i]), NULL, &mult, NULL);
  for (i = 0; i < 4; i++) pthread_join(tid[i], NULL);
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 5; j++) {
      printf("%2d ", mat3[i][j]);
		}
		printf("\n");
  }
  // shmdt(mat3);
  // shmctl(shmid, IPC_RMID, NULL);
}
