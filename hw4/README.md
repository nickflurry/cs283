To run: 
	make

	You can then run the program through the terminal like so. 

	./main test blat he


The directory is hard coded in. And the directory is './sub' in this case. 

Clean up: 
	make clean



Files in './sub':
	not: 
	 fdsaf  sdfa asdf sd

	test.txt
	 	This is a WRONG
		he is a monster

	test2.txt:
		This is a test.
		But dont forget this is a test too.

Output after program is run. 
	Stephens-MacBook-Pro:hw4 stephenslatky$ ./main test blat he
	./sub/not
	./sub/test.txt
	This is a WRONG
	blathe is a monster
	./sub/test2.txt
	This is a blat.
	But dont forget this is a blat too.