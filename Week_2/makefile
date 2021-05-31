all: scrabble caesar substitution readability

scrabble: scrabble.c
	gcc -o scrabble scrabble.c

caesar: caesar.c
	gcc -o caesar caesar.c

substitution: substitution.c
	gcc -o substitution substitution.c

readability: readability.c coleman_liam_index
	gcc -o readability readability.c -lm

coleman_liam_index: coleman_liam_index.h