all: exec

main.o: main.c
	gcc -c main.c -o main.o

baseFunctions.o: baseFunctions.c
	gcc -c baseFunctions.c -o baseFunctions.o

combatFunctions.o: combatFunctions.c
	gcc -c combatFunctions.c -o combatFunctions.o

exec: baseFunctions.o combatFunctions.o main.o
	gcc main.o baseFunctions.o combatFunctions.o -o exec

#Delete all files if you are using Windows OS
cleanW:
	del *.o
	del *.exe
	@echo "Tout les fichiers ont ete supprimés"

#Delete all files if you are using Linux OS
clean: 
	rm -f *.o exec
	@echo "Tout les fichiers ont ete supprimés"

