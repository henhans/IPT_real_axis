CC = g++ 
CFLAGS = #-O3
LFLAGS = #
OBJECTS = init.o routines.o pt.o main.o

#output.txt: main.exe
#	./main.exe > output.txt

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< 
