#ifndef _shim_iostream__h__
#define _shim_iostream__h__

/* Use newer <iostream> version */
#include <iostream>

using namespace std;

#define ifstream local_ifstream

class local_ifstream {
  public:
    local_ifstream();
    void open(const char *path);
    void close();

    void operator>> (char& c);
    void operator>> (int& i);

  private:
    int const *next_i;
    char const *next_c;
};

#endif
