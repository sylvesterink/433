CC = g++
CFLAGS = -c -g -Wall -pedantic
#CFLAGS = -c -s -O2 -Wall -pedantic
LIB = -lm
LDFLAGS = -lpthread -L.
SOURCES = main.cpp Buffer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = pcsolver.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)
