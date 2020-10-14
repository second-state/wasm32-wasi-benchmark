#define _DEFAULT_SOURCE
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  DIR *dir = opendir(".");
  if (dir == NULL) {
    printf("opendir failed: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  for (struct dirent *dirent = readdir(dir); dirent != NULL;
       dirent = readdir(dir)) {
    printf("name:%s type:%u\n", dirent->d_name, (unsigned int)dirent->d_type);
  }
  if (closedir(dir) < 0) {
    printf("closedir failed: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  int testfile = openat(3, "testfile", O_RDWR);
  if (testfile < 0) {
    printf("open failed: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  if (close(testfile) < 0) {
    printf("close failed: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
