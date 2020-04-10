#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>

void mv(char *file) {
  char *ext = strrchr(file, '.');
  if(ext) {
    char n[10];
    strcpy(n, ext);
    ext = "";
    for (size_t i = 0; i < strlen(n); i++) {
      n[i] = tolower(n[i]);
    }
    ext = n;
  }
  if(!ext || ext == file) ext = ".Unknown";
  mkdir(ext + 1, 0755);
  size_t len = strlen(ext + 1) + strlen(file) + sizeof("/");
  char *tmp = malloc(len);
  sprintf(tmp, "%s/%s", ext + 1, file);
  rename(file, tmp);
  free(tmp);
}
void mv2(char *file, char *path) {
  char *ext = strrchr(file, '.');
  if(ext) {
    char n[10];
    strcpy(n, ext);
    ext = "";
    for (size_t i = 0; i < strlen(n); i++) {
      n[i] = tolower(n[i]);
    }
    ext = n;
  }
  if(!ext || ext == file) ext = ".Unknown";
  mkdir(ext + 1, 0755);
  size_t len = strlen(ext + 1) + strlen(file) + sizeof("/");
  char *tmp = malloc(len);
  sprintf(tmp, "%s/%s", ext + 1, file);
  size_t len2 = strlen(path) + strlen(file) + sizeof("/");
  char *tmp2 = malloc(len2);
  sprintf(tmp2, "%s/%s", path, file);
  rename(tmp2, tmp);
  free(tmp);
}
int main(int argc, char *argv[]) {
  if (!strcmp(argv[1], "*")) {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
      while ((dir = readdir(d)) != NULL) {
        if (dir->d_type == DT_REG) {
          mv(dir->d_name);
        };
      }
    closedir(d);
    }
  } else if (!strcmp(argv[1], "-d")) {
    DIR *d;
    struct dirent *dir;
    d = opendir(argv[2]);
    if (d) {
      while ((dir = readdir(d)) != NULL) {
        if (dir->d_type == DT_REG) {
          mv2(dir->d_name, argv[2]);
        };
      }
    closedir(d);
    }
  } else if (!strcmp(argv[1], "-f")) {
      for(int i = 2; i < argc; i++) {
          mv(argv[i]);
      }
  }
  return 0;
}
