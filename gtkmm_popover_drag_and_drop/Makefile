CFLAGS=-c -Wall
EXECUTABLE=bug_sample_app

CC=g++
# 
SOURCES= main.cpp sample_window.cpp 
SOURCES	:= $(addprefix src/,$(SOURCES))
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ `pkg-config gtkmm-3.0 --libs`

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@  -I./src `pkg-config gtkmm-3.0 --cflags` -g

clean:
	rm -rf src/*.o $(EXECUTABLE)
