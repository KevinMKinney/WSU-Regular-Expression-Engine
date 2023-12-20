.SUFFIXES: .c .o
CCFLAGS = -std=c99 -pedantic -Wall
OBJS = REE.o REEfunc.o
EXEC = REE
	
run: ${EXEC}
	./${EXEC}

default:${EXEC}

clean:
	rm -f ${EXEC}
	rm -f *.o

${EXEC}:${OBJS}
	gcc ${FLAGS} -o ${EXEC} ${OBJS}

.c.o:
	gcc ${FLAGS} -c $<
	
REE.o: REE.c REE.h
REEfunc.o: REEfunc.c REE.h
