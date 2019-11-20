all: tokenizer

tokenizer: input.txt src/main.c src/tokenizer.c src/write.c
	@gcc -o src/tokenizer src/main.c src/tokenizer.c src/write.c
	@src/tokenizer
	@rm src/tokenizer

test:
	@gcc -o tests/tokenizer.t tests/tokenizer.c
	@gcc -o tests/vm.t tests/vm.c -lm
	@prove -v tests/*.t
	@rm tests/*.t tests/*.txt
