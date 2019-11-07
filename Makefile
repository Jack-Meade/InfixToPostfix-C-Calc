#all: tokens.txt code.txt i2pcalc
target: i2pcalc

tokens.txt: tokenizer.c input.txt
	@gcc -o tokenizer.o tokenizer.c
	@./tokenizer.o
	@rm tokenizer.o

code.txt: code_generator.c i2p.txt
	@gcc -o code_generator.o code_generator.c
	@./code_generator.o
	@rm code_generator.o

i2pcalc: vm.c code.txt
	@gcc -o i2pcalc vm.c -lm
	@./i2pcalc
	@rm i2pcalc

clean:
	rm tokens.txt
	rm i2p.txt
	rm code.txt
