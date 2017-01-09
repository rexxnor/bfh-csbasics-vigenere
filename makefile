all: vigenere

clean:
	rm *.o *~

vigenere: vigenere.c
	gcc vigenere.c -o vigenere -g
