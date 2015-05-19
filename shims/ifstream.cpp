#include "iostream.h"

#include "datafile/texture2.h"
#include "datafile/level1.h"
#include "datafile/level2.h"
#include "datafile/level3.h"
#include "datafile/level4.h"
#include "datafile/level5.h"

local_ifstream::local_ifstream():next_i(NULL),next_c(NULL) {
}

void local_ifstream::open(const char *path) {
  if (!strcmp(path, "texture2.txt")) {
    next_i = &datafile_texture2[0];
  }
  else if (!strcmp(path, "level1.lv")) {
    next_c = &datafile_level1[0];
  }
  else if (!strcmp(path, "level2.lv")) {
    next_c = &datafile_level2[0];
  }
  else if (!strcmp(path, "level3.lv")) {
    next_c = &datafile_level3[0];
  }
  else if (!strcmp(path, "level4.lv")) {
    next_c = &datafile_level4[0];
  }
  else if (!strcmp(path, "level5.lv")) {
    next_c = &datafile_level5[0];
  }
  else {
    fprintf(stderr, "local_ifstream::open error, unknown file: %s\n", path);
    exit(1);
  }
}

void local_ifstream::close() {
}

void local_ifstream::operator>> (char& c) {
  c = *next_c++;
}

void local_ifstream::operator>> (int& i) {
  i = *next_i++;
}
