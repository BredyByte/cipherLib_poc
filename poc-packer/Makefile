CC = gcc
CFLAGS = -fPIC -O2 -Wall -Wextra -Werror
DEBUGFLAGS = -g -O0
LDFLAGS = -shared

LIBDIR = ./libB
LIBSRC = $(LIBDIR)/libB.c
LIBHDR = $(LIBDIR)/libB.h
LIBOUT = $(LIBDIR)/libB.so

MAIN_SRC = ./main.c
MAIN_BIN = ./main

RPATH = \$$ORIGIN/libB

.PHONY: all build-lib build-main build-debug clean

all: build-lib build-main

build-lib: $(LIBSRC) $(LIBHDR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(LIBOUT) $(LIBSRC)
	@echo "-> Librería construida: $(LIBOUT)"

build-main: $(MAIN_SRC)
	$(CC) -o $(MAIN_BIN) $(MAIN_SRC) -I$(LIBDIR) -L$(LIBDIR) -lB -ldl -Wl,-rpath=$(RPATH)
	@echo "-> Ejecutable construido: $(MAIN_BIN)"

build-debug:
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(MAIN_BIN)_debug $(MAIN_SRC) -I$(LIBDIR) -L$(LIBDIR) -lB -ldl -Wl,-rpath=$(RPATH)

clean:
	-rm -f $(LIBOUT) $(MAIN_BIN)
	@echo "-> Limpieza completada"
