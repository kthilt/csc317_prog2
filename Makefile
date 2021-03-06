CC = gcc -g -Wall
CXX = g++ -g -Wall -std=c++11
LIBS = 
FLAGS =
CXXFLAGS =
EXECS = b17
DEBUG_EXECS = 
O_FILES = b17.o b17_functions.o
TEMPORARY_FILES = *~ output.txt

all: $(EXECS)

debug: $(DEBUG_EXECS)
   
b17: $(O_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS) -lm

.c:
	$(CC) -o $@ $@.c

.cpp:
	$(CXX) $(CXXFLAGS) -o $@ $@.cpp

clean:
	$(RM) $(EXECS) $(DEBUG_EXECS) $(O_FILES) $(TEMPORARY_FILES)
