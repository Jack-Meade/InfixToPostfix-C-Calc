all: tokens.txt i2p.txt code.txt i2pcalc

tokens.txt: tokenizer.c input.txt write.h
	@gcc -o tokenizer.o tokenizer.c
	@./tokenizer.o
	@rm tokenizer.o

i2p.txt: i2p.c tokens.txt write.h
	@gcc -o i2p.o i2p.c
	@./i2p.o
	@rm i2p.o

code.txt: code_generator.c i2p.txt write.h
	@gcc -o code_generator.o code_generator.c
	@./code_generator.o
	@rm code_generator.o

i2pcalc: vm.c code.txt
	@gcc -o i2pcalc vm.c -lm
	@./i2pcalc
	@rm i2pcalc

test:
	@tests/tokenizer.t
