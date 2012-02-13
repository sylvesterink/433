CC = g++
CFLAGS = -c -g -Wall -pedantic
LIB = -lm
LDFLAGS = -L.
SOURCES = main.cpp ReadyQueue.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = ProjectOne.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)
