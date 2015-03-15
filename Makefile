SOURCE_FILES=                      \
  shims/graphics.cpp               \
  shims/ifstream.cpp               \
  original_source/bclass.cpp       \
  original_source/tankbeta.cpp     \
  original_source/tclass.cpp       \
  original_source/tscreen.cpp      \
  third_party_source/apstring.cpp

GCC_FLAGS=-std=c++98 -w

tankbeta: ${SOURCE_FILES}
	g++ `pkg-config SDL_ttf --cflags` \
	    -I./shims                     \
	    -I./third_party_source        \
	    -o tankbeta                   \
	    ${GCC_FLAGS}                  \
	    ${SOURCE_FILES}               \
	    `pkg-config SDL_ttf --static --libs`

tankbeta.html: ${SOURCE_FILES}
	emcc -I./shims                     \
	     -I./third_party_source        \
	     -o tankbeta.html              \
	     ${GCC_FLAGS}                  \
	     ${SOURCE_FILES}

clean:
	rm -f tankbeta tankbeta.js tankbeta.html
