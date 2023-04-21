CC=clang++
CFLAGS= -Wall -Wextra -pedantic
LDFLAGS=-L/opt/homebrew/lib -fsanitize=address -lSDL2
CPPFLAGS=-I/opt/homebrew/include -I/opt/homebrew/include/SDL2
CFLAGS += $(CPPFLAGS) -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls

EXECUTABLE=play
SOURCES=main.cpp Complex.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f *.o $(EXECUTABLE)
