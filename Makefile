CC = icpc#mpicxx#icpc
FLAGS = -D_OMP -openmp
#LFLAGS = #
OBJECTS = init.o routines.o pt.o main.o

#output.txt: main.exe
#	./main.exe > output.txt

main.exe: $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o main.exe

%.o : %.cpp
	$(CC) $(FLAGS) -c -o $@ $< 

clean: 
	rm -f *.o
