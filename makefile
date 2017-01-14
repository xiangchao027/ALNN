CC = clang
cnn.o :
	$(CC) -o cnn.o cnn.c
clean :
	rm *.o
test :
	./cnn.o
