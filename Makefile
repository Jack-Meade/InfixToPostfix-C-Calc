all: tokens.txt i2pcalc

tokens.txt: tokenizer.c input.txt
	@gcc -o tokenizer.o tokenizer.c
	@./tokenizer.o
	@rm tokenizer.o

i2pcalc: vm.c code.txt
	@gcc -o i2pcalc vm.c -lm
	@./i2pcalc
	@rm i2pcalc
