# GNU Makefile

CC = gcc
CCFLAGS = -Wall
LDFLAGS = 

PROGRAM   = nqueens
SRCS      = main.c nqueens.c
OBJS      = $(SRCS:.c=.o)

.SUFFIXES: .c .o

.c.o: 
	$(CC) -c $(CCFLAGS) $<

all: $(PROGRAM) 

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(SRCS) $(CCFLAGS) $(LDFLAGS)

clean:
	/bin/rm -f $(OBJS) $(PROGRAM)
