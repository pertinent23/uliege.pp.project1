### 
## Makefile skeleton
## INFO0030: Projet 1
## 
### 

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LD=gcc
LDFLAGS=
AT=tar
ATFLAGS=-zcvf
DT=doxygen

# Files
EXEC=pnm
MODULES=utils.c pnm.c main.c
OBJECTS=utils.o pnm.o main.o
OUTPUT=project_1.tar.gz
CONFIG=doxygen.config

## Rules

all: $(EXEC)

pnm: $(OBJECTS)
	$(LD) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

pnm.o: pnm.c
	$(CC) -c pnm.c -o pnm.o $(CFLAGS)

utils.o: utils.c
	$(CC) -c utils.c -o utils.o $(CFLAGS)

clean:
	rm -f *.o *.ppm *.pgm .*pbm $(EXEC) $(OUTPUT) *~

archive: clean
	$(AT) $(ATFLAGS) $(OUTPUT) *

doc:
	$(DT) $(CONFIG)
