CC = clang
LIBS = -lm -ldl
CFLAGS =  -Wall

NAME = iproc
DEBUG = ./debug
RELEASE = ./release

.PHONY: all debug release clean

all: release

debug: ../core/iproc.c linux.c
	mkdir -p $@
	$(CC) $(CFLAGS) $(LIBS) -o $(DEBUG)/$(NAME) $^ -g

release: ../core/iproc.c linux.c
	mkdir -p $@
	$(CC) $(CFLAGS) $(LIBS) -o $(RELEASE)/$(NAME) $^

clean:
	rm -f $(DEBUG)/*
	rm -f $(RELEASE)/*
