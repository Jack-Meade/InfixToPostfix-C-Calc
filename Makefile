all: tokens.txt i2p.txt code.txt i2pcalc

tokens.txt: src/tokenizer.c input.txt src/write.h
	@gcc -o tokenizer.o src/tokenizer.c
	@./tokenizer.o
	@rm tokenizer.o

i2p.txt: src/i2p.c output/tokens.txt src/write.h
	@gcc -o i2p.o src/i2p.c
	@./i2p.o
	@rm i2p.o

code.txt: src/code_generator.c output/i2p.txt src/write.h
	@gcc -o code_generator.o src/code_generator.c
	@./code_generator.o
	@rm code_generator.o

i2pcalc: src/vm.c output/code.txt
	@gcc -o i2pcalc src/vm.c -lm
	@./i2pcalc
	@rm i2pcalc

test:
	@gcc -o tests/tokenizer.t tests/tokenizer.c
	@prove -v tests/*.t
	@rm tests/*.t tests/input.txt
