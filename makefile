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

debug: baseFunctions.o interfaceFunctions.o combatFunctions.o movesFunctions.o effectsFunctions.o attacksFunctions.o ultimateFunctions.o main.o
	gcc -g main.o baseFunctions.o interfaceFunctions.o combatFunctions.o movesFunctions.o effectsFunctions.o attacksFunctions.o ultimateFunctions.o -o cy-fighter -lm

exec: baseFunctions.o interfaceFunctions.o combatFunctions.o movesFunctions.o effectsFunctions.o attacksFunctions.o ultimateFunctions.o main.o
	gcc main.o baseFunctions.o interfaceFunctions.o combatFunctions.o movesFunctions.o effectsFunctions.o attacksFunctions.o ultimateFunctions.o -o cy-fighter -lm;./cy-fighter

test: test.c
	gcc -o test test.c

#Delete all files if you are using Windows OS
cleanw:
	del *.o *.exe cy-fighter test
	@echo "Tout les fichiers ont ete supprimés"

#Delete all files if you are using Linux OS
clean: 
	rm -f *.o cy-fighter test
	@echo "Tout les fichiers ont ete supprimés"

