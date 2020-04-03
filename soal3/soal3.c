#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

static void mkfolder(const char *dir) {
	char *ext = strrchr(dir, '.');
 	mkdir(dir, 0755);
}
static void mv(const char *file) {
  char *ext = strrchr(file, '.');
  if(!ext || ext == file) {
    /* code */
  } else {
    mkfolder(ext + 1);
    size_t len = strlen(ext + 1) + strlen(file) + sizeof("/");
    char *tmp = malloc(len);
    sprintf(tmp, "%s/%s", ext + 1, file);
    rename(file, tmp);
    free(tmp);
  }
}
int main(int argc, char *argv[]) {
  if(!strcmp(argv[2], "*")) {
    struct dirent *dir;
    DIR *d = opendir(".");
    if (d == NULL) {
      printf("Could not open current directory" );
      return 0;
    }

    while ((dir = readdir(d)) != NULL) {
      if (dir->d_type == DT_REG)
        printf("%s\n", dir->d_name);
    }

    closedir(d);
  } else if (!strcmp(argv[1], "-d")) {
  } else if (!strcmp(argv[1], "-f")) {
      for(int i = 2; i < argc; i++) {
          mv(argv[i]);
      }
  }
  return 0;
}
