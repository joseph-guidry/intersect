#
#
# 
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

all: intersect

intersect: intersect.c avlIntersect.o
	$(CC) $(CFLAGS) -o intersect intersect.c avlIntersect.o

avlIntersect.o: avlIntersect.c avlIntersect.h
	$(CC) -c -o avlIntersect.o avlIntersect.c

debug: intersect.c avlIntersect.o
	$(CC) $(CFLAGS) -g -o intersect intersect.c avlIntersect.o

profile: intersect.c avlIntersect.c
	gcc -Wall -pg -o profile intersect.c avlIntersect.c
	./profile intersect.c avlIntersect.c
	gprof profile gmon.out > gprof_output.txt

clean:
	rm -f *.o intersect


