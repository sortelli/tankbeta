SOURCE_FILES=                      \
  original_source/bclass.cpp       \
  original_source/tankbeta.cpp     \
  original_source/tclass.cpp       \
  original_source/tscreen.cpp      \
  third_party_source/apstring.cpp

GCC_FLAGS="-Wno-extra-tokens"

tankbeta:
	gcc -I./shims -I./third_party_source -o tankbeta ${GCC_FLAGS} ${SOURCE_FILES}
