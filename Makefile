CC=gcc

CFLAGS=-Wall -Wextra --pedantic

SRC=cache.cpp

OBJ=$(SRC:.cpp=.o)

EXEC=cacheSim

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) -lstdc++

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJ) *.o
