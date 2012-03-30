CC = g++
CFLAGS = -c -g -Wall -pedantic
#CFLAGS = -c -s -O2 -Wall -pedantic
LIB = -lm
LDFLAGS = -L.
SOURCES = main.cpp Event.cpp Process.cpp System.cpp FCFSSystem.cpp SJFSystem.cpp random.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = cpusim.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)
