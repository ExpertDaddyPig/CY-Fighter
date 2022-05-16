all: exec

main.o: main.c
	gcc -c main.c -o main.o

baseFunctions.o: baseFunctions.c
	gcc -c baseFunctions.c -o baseFunctions.o

exec: main.o baseFunctions.o
	gcc main.o baseFunctions.o -o exec

#Delete all files if you are using Windows OS
cleanW:
	del main.o
	del baseFunctions.o
	del exec.exe
	@echo "Tout les fichiers ont ete supprimés"

#Delete all files if you are using Linux OS
clean: 
	rm -f *.o exec
	@echo "Tout les fichiers ont ete supprimés"

