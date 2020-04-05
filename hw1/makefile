a.out : hw1.o main.o
	gcc -o a.out hw1.o main.o
hw1.o : hw1.c
	gcc -c -o hw1.o hw1.c
main.o: main.c
	gcc -c -o main.o main.c
clean :
	rm *.o a.out
