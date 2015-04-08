CC = gcc -g -Wall
CPP = g++ -g -Wall
LIBS = 
FLAGS =
EXECS = b17
DEBUG_EXECS = 
O_FILES = b17.o parse_object_file.o

all: $(EXECS)

debug: $(DEBUG_EXECS)
   
b17: $(O_FILES)
	$(CPP) $(FLAGS) -o $@ $^ $(LIBS) -lm

.c:
	$(CC) -o $@ $@.c

.cpp:
	$(CPP) -o $@ $@.cpp

clean:
	$(RM) $(EXECS) $(DEBUG_EXECS) $(O_FILES)
