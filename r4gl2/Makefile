# Project: R4GL
# Makefile created by Dev-C++ 4.9.9.2

CC   = gcc
RES  =
OBJ  = redam.o sisgl.o graf.o $(RES)
LINKOBJ  = redam.o sisgl.o graf.o $(RES)
LIBS =  -lGL
INCS =
BIN  = r4gl
CFLAGS = $(INCS) -O2
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before r4gl all-after



clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o r4gl $(LIBS) -s

redam.o: redam.c
	$(CC) -c redam.c -o redam.o $(CFLAGS)

sisgl.o: sisgl.c
	$(CC) -c sisgl.c -o sisgl.o $(CFLAGS)
graf.o: graf.c
	$(CC) -c graf.c -o graf.o $(CFLAGS)

