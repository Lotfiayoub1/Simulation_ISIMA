
output: main.o middle_square.o coin_tossing.o regular_dice.o lgcs.o
	gcc main.o middle_square.o coin_tossing.o regular_dice.o lgcs.o -o output

main.o: main.c 
	gcc -c main.c 

middle_square.o: middle_square.c middle_square.h 
	gcc -c middle_square.c

coin_tossing.o: coin_tossing.c coin_tossing.h 
	gcc -c coin_tossing.c

lgcs.o: lgcs.c lgcs.h 
	gcc -c lgcs.c

regular_dice.o: regular_dice.c regular_dice.h 
	gcc -c regular_dice.c
clean:
	rm *.o output
