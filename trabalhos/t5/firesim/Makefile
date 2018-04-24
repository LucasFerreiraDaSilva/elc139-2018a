CXX       = g++
CXXFLAGS  = -Wall -I.

PROGRAM   = firesim
SRCS      = firesim.cpp Random.cpp Forest.cpp
OBJS      = $(SRCS:.cpp=.o)

.SUFFIXES: .cpp .o

.cpp.o: 
	$(CXX) -c $(CXXFLAGS) $<

all: $(PROGRAM) 

$(PROGRAM): $(OBJS)
	$(CXX) -o $(PROGRAM) $(SRCS) $(CXXFLAGS) $(LDFLAGS)

clean:
	/bin/rm -f $(OBJS) $(PROGRAM)
