#Coloque o caminho até Projeto aqui
prefix=/home/USER/Projeto
bindir=$(prefix)/bin 
CC=g++
CFLAGS=-W -Wall -ansi -pedantic -pthread -std=c++14
EXEC=teste
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
all: $(EXEC)
@echo "Compilando Projeto"
@echo "O patrao foi compilado"
#A linha que vai compilar sub-make
@cd sub-make && $(MAKE)
teste: $(OBJ)
@$(CC) -o $@ $^ 
%.o: %.c
@$(CC) -o $@ -c $< $(CFLAGS)
main.o: main.c teste.h
@$(CC) -o $@ -c $< $(CFLAGS) 
#Entao depois e so executar make e depois make install
install:all
@mv $(EXEC) $(bindir)/
.PHONY: clean mrproper
clean: 
@rm -rf *.o *~ 
# E a mesma coisa que dar um F4 dentro da pasta sub-make
# e escrever make clean 
@cd sub-make && $(MAKE) $@ 
mrproper: clean
@cd bin && rm -rf $(EXEC)
#modificamos aqui tambem
@cd sub-make && $(MAKE) $@