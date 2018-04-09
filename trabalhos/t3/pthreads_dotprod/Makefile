# GNU Makefile

CC = gcc 
CCFLAGS = -Wall
LDFLAGS = -pthread
TARGET = pthreads_dotprod pthreads_dotprod2

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

%: %.o
	$(CC) $(LDFLAGS) $^ -o $@ 

all: $(TARGET)

# Dependencias

pthreads_dotprod: pthreads_dotprod.c
pthreads_dotprod2: pthreads_dotprod2.c

clean:
	rm -f *.o *~ $(TARGET)
