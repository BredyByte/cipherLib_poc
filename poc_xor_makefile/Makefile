CC = gcc
CFLAGS = -fPIC -O2 -Wall -Wextra
LDFLAGS = -shared

LIBDIR = ./libB
LIBSRC = $(LIBDIR)/libB.c
LIBHDR = $(LIBDIR)/libB.h
LIBOUT = $(LIBDIR)/libB.so
ENCOUT = $(LIBDIR)/libB.so.enc
DECOUT = $(LIBDIR)/libB.so.dec

MAIN_SRC = ./main.c
MAIN_BIN = ./main

PACKER_SRC = xor_packer.c
PACKER_BIN = ./xor_packer

RPATH = \$$ORIGIN/libB

.PHONY: all build-lib xor_packer pack unpack build-main clean

all: build-lib build-main

# construir la librería .so original
build-lib: $(LIBSRC) $(LIBHDR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(LIBOUT) $(LIBSRC)
	@echo "-> Librería construida: $(LIBOUT)"

# compilar xor_packer
xor_packer: $(PACKER_SRC)
	$(CC) -o $(PACKER_BIN) $(PACKER_SRC)
	@echo "-> xor_packer compilado: $(PACKER_BIN)"

# cifrar la librería con xor (genera libB.so.enc)
# usa la clave MIRADA por defecto; puedes cambiarla desde la línea de comandos: make pack KEY=mikey
pack: xor_packer build-lib
	@if [ -z "$(KEY)" ]; then KEY=mi_clave; else KEY=$(KEY); fi; \
	echo "-> Usando KEY='$$KEY'"; \
	$(PACKER_BIN) $(LIBOUT) $(ENCOUT) "$$KEY"

# descifrar la librería (genera libB.so.dec)
unpack: xor_packer
	@if [ ! -f $(ENCOUT) ]; then echo "-> No existe $(ENCOUT). Ejecuta 'make pack' primero."; exit 1; fi; \
	if [ -z "$(KEY)" ]; then KEY=mi_clave; else KEY=$(KEY); fi; \
	echo "-> Desencriptando $(ENCOUT) -> $(DECOUT) con KEY='$$KEY'"; \
	$(PACKER_BIN) $(ENCOUT) $(DECOUT) "$$KEY"

# construir el main (enlaza dinámicamente; asume que libB.so está disponible si quieres ejecutar sin unpack)
build-main: $(MAIN_SRC)
	$(CC) -o $(MAIN_BIN) $(MAIN_SRC) -I$(LIBDIR) -L$(LIBDIR) -lB -ldl -Wl,-rpath=$(RPATH)
	@echo "-> Ejecutable construido: $(MAIN_BIN)"

# limpieza
clean:
	-rm -f $(LIBOUT) $(ENCOUT) $(DECOUT) $(MAIN_BIN) $(PACKER_BIN)
	@echo "-> Limpieza completada"
