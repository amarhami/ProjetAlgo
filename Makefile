run : compil
	./main


compil: main.c
	gcc -Wall -o main main.c

clean:
	rm -f compil