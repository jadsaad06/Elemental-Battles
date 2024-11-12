CC = g++
FLAGS = -std=c++17 -g -Wall

SOURCES = main.cpp health.cpp player.cpp card.cpp
OBJS = $(SOURCES:.cpp=.o)

DEPS = main.h health.h player.h card.h deck.h deck.tpp

%.o: %.cpp $(DEPS)
	$(CC) $(FLAGS) -c -o $@ $<

main: $(OBJS)
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -f $(OBJS) main
