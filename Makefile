target: i2pcalc

i2pcalc: input.txt src/main.c src/tokenizer.c src/i2p.c src/code_generator.c src/vm.c src/write.c
	@gcc -o i2pcalc src/main.c src/tokenizer.c src/i2p.c src/code_generator.c src/vm.c src/write.c -lm
	@./i2pcalc
	@rm ./tokenizer

test:
	@gcc -o tests/tokenizer.t tests/tokenizer.c src/tokenizer.c src/write.c
	@gcc -o tests/vm.t tests/vm.c src/vm.c src/write.c -lm 
	@prove -v tests/*.t
	@rm tests/*.t tests/*.txt
