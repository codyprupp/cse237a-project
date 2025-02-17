all:
	gcc -o test test.c ads1115.c -lwiringPi -lpthread

clean:
	rm -rf test
