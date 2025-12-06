CC=gcc
FLAGS=-Wextra -Wall -g
TARGETS = 1 2 3 4 5

.PHONY: all clean

all: $(TARGETS)

$(TARGETS):
	$(CC) $(FLAGS) day$@/part1.c -lm -o r-$@-1; $(CC) $(FLAGS) day$@/part2.c -lm -o r-$@-2

clean:
	-rm r*