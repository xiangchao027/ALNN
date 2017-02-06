CC = clang
DEBUG = -D __DEBUG__
TARGETS = main.o check/t_main.o
$(TARGETS) :
	$(CC) -o main.o $(DEBUG) main.c
	$(CC) -o check/t_main.o $(DEBUG) check/t_main.c

clean :
	@-rm *.o && rm check/*.o && echo "object files cleaned!"

test : $(TARGETS)
	@-./check/t_main.o && ./main.o 1
