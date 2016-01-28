CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

BIN=assignment3_starwars
SRCS=assignment3_starwars.cpp gl_framework.cpp shader_util.cpp hierarchy_node.cpp starwars.cpp texture.cpp Basics.cpp 
INCLUDES=gl_framework.hpp shader_util.hpp assignment3_starwars.hpp hierarchy_node.hpp starwars.hpp include.hpp texture.hpp Basics.hpp

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN) final_output.txt keyframes.txt
