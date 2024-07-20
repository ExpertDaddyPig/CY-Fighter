all: exec

main.o: main.c
	gcc -c main.c -o main.o

baseFunctions.o: baseFunctions.c
	gcc -c baseFunctions.c -o baseFunctions.o

combatFunctions.o: combatFunctions.c
	gcc -c combatFunctions.c -o combatFunctions.o

movesFunctions.o: movesFunctions.c
	gcc -c movesFunctions.c -o movesFunctions.o

attacksFunctions.o: attacksFunctions.c
	gcc -c attacksFunctions.c -o attacksFunctions.o

effectsFunctions.o: effectsFunctions.c
	gcc -c effectsFunctions.c -o effectsFunctions.o

exec: baseFunctions.o combatFunctions.o movesFunctions.o effectsFunctions.o attacksFunctions.o main.o
	gcc main.o baseFunctions.o combatFunctions.o movesFunctions.o effectsFunctions.o attacksFunctions.o -o cy-fighter

#Delete all files if you are using Windows OS
cleanw:
	del *.o *.exe cy-fighter
	@echo "Tout les fichiers ont ete supprimés"

#Delete all files if you are using Linux OS
clean: 
	rm -f *.o cy-fighter
	@echo "Tout les fichiers ont ete supprimés"

