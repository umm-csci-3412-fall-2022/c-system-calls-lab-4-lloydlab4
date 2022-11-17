#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
  
  struct stat buf;
  
  int not_exist = stat(path, &buf);
  if(not_exist == 0) {
    return S_ISDIR(buf.st_mode);
  } else {
    char* error_message = (char*) path;
    strcat(error_message, " does not exist");
    perror(path);
    exit(1);
  }
}
/* 
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char*);

void process_directory(const char* path) {
  num_dirs++;
  DIR *dir = opendir(path);
  chdir(path);
  
  struct dirent *entry;
  errno = 0;
  while(((entry = readdir(dir)) != NULL) && errno == 0) {
    if(is_dir(entry->d_name)) {
      if(strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".") != 0) {
        process_directory(entry->d_name);
      }
    } else {
      num_regular++;
    }
  }
  if(errno != 0) {
    char* error_message = (char*) path;
    strcat(error_message, " returned error");
    perror(path);
    exit(1);
  } else {
    closedir(dir);
    chdir("..");
  }
}

void process_file(const char* path) {
  num_regular++;
}

void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
