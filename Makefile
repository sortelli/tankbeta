SOURCE_FILES=                      \
  original_source/bclass.cpp       \
  original_source/tankbeta.cpp     \
  original_source/tclass.cpp       \
  original_source/tscreen.cpp      \
  third_party_source/apstring.cpp

GCC_FLAGS=-std=c++98 -Wno-dangling-else -Wno-extra-tokens -ferror-limit=100

tankbeta:
	gcc -I./shims -I./third_party_source -o tankbeta ${GCC_FLAGS} ${SOURCE_FILES}
