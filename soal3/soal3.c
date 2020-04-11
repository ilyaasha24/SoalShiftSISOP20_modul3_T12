#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <dirent.h>
#include <ctype.h>
struct args {
    char* file;
    char* path;
};
void *mv(void *pass) {
  char *file = ((struct args*)pass)->file, *path = ((struct args*)pass)->path;
  char *ext = strrchr(file, '.');
  if (ext) {
    char n[10];
    strcpy(n, ext);
    for (size_t i = 0; i < strlen(n); i++) n[i] = tolower(n[i]);
    ext = n;
  }
  if (!ext || ext == file || !strcmp(ext + 1, "*")) ext = ".Unknown";
  mkdir(ext + 1, 0755);
  size_t len = strlen(ext + 1) + strlen(file) + sizeof("/"), len2 = strlen(path) + strlen(file) + sizeof("/");
  char *tmp = malloc(len), *tmp2 = malloc(len2);
  sprintf(tmp, "%s/%s", ext + 1, file);
  sprintf(tmp2, "%s/%s", path, file);
  rename(tmp2, tmp);
  free(tmp);
}
int main(int argc, char *argv[]) {
  if (argc < 2) perror("Error: Missing Arguments");
  pthread_t tid[100];
  if (!strcmp(argv[1], "*") || !strcmp(argv[1], "-d")) {
    DIR *d;
    struct dirent *dir;
    if (!strcmp(argv[1], "*")) argv[2] = ".";
    d = opendir(argv[2]);
    if (d) {
      int i = 0;
      while ((dir = readdir(d)) != NULL) {
        if (dir->d_type == DT_REG && strcmp(dir->d_name, "soal3")) {
          struct args *pass = (struct args *)malloc(sizeof(struct args));
          pass->file = dir->d_name;
          pass->path = argv[2];
          pthread_t tid[i];
          pthread_create(&tid[i++], NULL, &mv, (void *)pass);
        };
      }
      for (i; i > 0; i--) pthread_join(tid[i], NULL);
    closedir(d);
    }
  } else if (!strcmp(argv[1], "-f")) {
    if (argc < 3) perror("Error: Missing Arguments");
    pthread_t tid[argc-2];
    for (int i = 2; i < argc; i++) {
      struct args *pass = (struct args *)malloc(sizeof(struct args));
      pass->file = argv[2];
      pass->path = ".";
      pthread_create(&tid[i-2], NULL, &mv, (void *)pass);
    }
    for (int i = 2; i < argc; i++) pthread_join(tid[i-2], NULL);
  } else {
    perror("Error: Undefined Arguments");
  }
  return 0;
}
