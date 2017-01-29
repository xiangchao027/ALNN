CC = clang
cnn.o :
	$(CC) -o main.o main.c
	$(CC) -o check/t_main.o check/t_main.c
clean :
	rm *.o && rm check/*.o
test :
	./check/t_main.o && ./main.o 1
