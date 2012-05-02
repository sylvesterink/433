CC = g++
CFLAGS = -c -g -Wall -pedantic
#CFLAGS = -c -s -O2 -Wall -pedantic
LIB = -lm
LDFLAGS = -lpthread -L.
SOURCES = main.cpp Simulator.cpp FIFOsim.cpp Page.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = pager.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)
