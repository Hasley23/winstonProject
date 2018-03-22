PROG = a
CC = cc
SRCS = l121.c fun.c
BIN = structure.dat
OBJS = $(SRCS:.c=.o)

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

clean:
	rm -f $(PROG) $(OBJS) $(BIN)

.c.o : fun.h; $(CC) -c $*.c