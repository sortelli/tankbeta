SOURCE_FILES=                      \
  shims/graphics.cpp               \
  shims/ifstream.cpp               \
  original_source/bclass.cpp       \
  original_source/tclass.cpp       \
  original_source/tscreen.cpp      \
  original_source/tankbeta.cpp     \
  third_party_source/apstring.cpp

GCC_FLAGS=-std=c++98 -w

tankbeta: ${SOURCE_FILES} original_source/tankbeta.cpp
	g++ `pkg-config SDL_ttf --cflags` \
	    -I./shims                     \
	    -I./third_party_source        \
	    -o tankbeta                   \
	    ${GCC_FLAGS}                  \
	    ${SOURCE_FILES}               \
	    `pkg-config SDL_ttf --static --libs`

annotated: annotated_source/annotated_source.cpp
	docco annotated_source/annotated_source.cpp

clean:
	rm -f tankbeta
