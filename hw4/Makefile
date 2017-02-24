PROG= main
OBJS= main.c csapp.c
CC= gcc
CFLAGS=	-Wall -g

all: ${PROG} 

${PROG}: ${OBJS}
	${CC} ${OBJS} -o ${PROG} -lpthread

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<   # Complies each file in the objs since it will indiviualy call each. It complies with the flags 
	 
clean:  # Removese every file that the make file could have created
	rm -f main
