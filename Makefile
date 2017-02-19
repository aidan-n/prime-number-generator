#Aidan
#Aidan.Normanly001@umb.edu

make:
	gcc -c -o fast-prime.o fast-prime.c
	gcc -o gcc -o fast-prime fast-prime.o -lm  -Werror -Wall -std=gnu99 -I.

clean:
	rm -rf fast-prime
	rm -rf primes.log
	find -name '*.o' -delete
