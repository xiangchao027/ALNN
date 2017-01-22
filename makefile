CC = clang
cnn.o :
	$(CC) -o main.o main.c
clean :
	rm *.o
test :
	./main.o 1
