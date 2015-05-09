SOURCE_FILES=                      \
  shims/graphics.cpp               \
  shims/ifstream.cpp               \
  original_source/bclass.cpp       \
  original_source/tclass.cpp       \
  original_source/tscreen.cpp      \
  third_party_source/apstring.cpp

GCC_FLAGS=-std=c++98 -w

tankbeta: ${SOURCE_FILES} original_source/tankbeta.cpp
	g++ `pkg-config SDL_ttf --cflags` \
	    -I./shims                     \
	    -I./third_party_source        \
	    -o tankbeta                   \
	    ${GCC_FLAGS}                  \
	    ${SOURCE_FILES}               \
	    original_source/tankbeta.cpp  \
	    `pkg-config SDL_ttf --static --libs`

tankbeta.html: ${SOURCE_FILES} emscripten_source/tankbeta-emscripten.cpp
	emcc -I./shims                     \
	     -I./third_party_source        \
	     -I./original_source           \
	     -o tankbeta.html              \
	     -s TOTAL_MEMORY=33554432      \
	     ${GCC_FLAGS}                  \
	     ${SOURCE_FILES}               \
	    emscripten_source/tankbeta-emscripten.cpp

clean:
	rm -f tankbeta tankbeta.js tankbeta.html
