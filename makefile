all: exec

main.o: main.c
	gcc -c main.c -o main.o

baseFunctions.o: baseFunctions.c
	gcc -c baseFunctions.c -o baseFunctions.o

interfaceFunctions.o: interfaceFunctions.c
	gcc -c interfaceFunctions.c -o interfaceFunctions.o

combatFunctions.o: combatFunctions.c
	gcc -c combatFunctions.c -o combatFunctions.o

movesFunctions.o: movesFunctions.c
	gcc -c movesFunctions.c -o movesFunctions.o

attacksFunctions.o: attacksFunctions.c
	gcc -c attacksFunctions.c -o attacksFunctions.o

ultimateFunctions.o: ultimateFunctions.c
	gcc -c ultimateFunctions.c -o ultimateFunctions.o

effectsFunctions.o: effectsFunctions.c
	gcc -c effectsFunctions.c -o effectsFunctions.o

main_debug.o: main.c
	gcc -g -c main.c -o main_debug.o

baseFunctions_debug.o: baseFunctions.c
	gcc -g -c baseFunctions.c -o baseFunctions_debug.o

interfaceFunctions_debug.o: interfaceFunctions.c
	gcc -g -c interfaceFunctions.c -o interfaceFunctions_debug.o

combatFunctions_debug.o: combatFunctions.c
	gcc -g -c combatFunctions.c -o combatFunctions_debug.o

movesFunctions_debug.o: movesFunctions.c
	gcc -g -c movesFunctions.c -o movesFunctions_debug.o

attacksFunctions_debug.o: attacksFunctions.c
	gcc -g -c attacksFunctions.c -o attacksFunctions_debug.o

ultimateFunctions_debug.o: ultimateFunctions.c
	gcc -g -c ultimateFunctions.c -o ultimateFunctions_debug.o

effectsFunctions_debug.o: effectsFunctions.c
	gcc -g -c effectsFunctions.c -o effectsFunctions_debug.o

debug: baseFunctions_debug.o interfaceFunctions_debug.o combatFunctions_debug.o movesFunctions_debug.o effectsFunctions_debug.o attacksFunctions_debug.o ultimateFunctions_debug.o main_debug.o
	gcc -g main_debug.o baseFunctions_debug.o interfaceFunctions_debug.o combatFunctions_debug.o movesFunctions_debug.o effectsFunctions_debug.o attacksFunctions_debug.o ultimateFunctions_debug.o -o cy-fighter-debug -lm

exec: baseFunctions.o interfaceFunctions.o combatFunctions.o movesFunctions.o effectsFunctions.o attacksFunctions.o ultimateFunctions.o main.o
	gcc main.o baseFunctions.o interfaceFunctions.o combatFunctions.o movesFunctions.o effectsFunctions.o attacksFunctions.o ultimateFunctions.o -o cy-fighter -lm;./cy-fighter

test: test.c
	gcc -o test test.c

#Delete all files if you are using Windows OS
cleanw:
	del *.o *.exe cy-fighter cy-fighter-debug test
	@echo "Tout les fichiers ont ete supprimés"

#Delete all files if you are using Linux OS
clean: 
	rm -f *.o cy-fighter cy-fighter-debug test
	@echo "Tout les fichiers ont ete supprimés"

