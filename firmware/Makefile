.PHONY: clean

all: main stepper-test sensor-test

main: main.o stepper.o ads1115.o music.o
	gcc main.o stepper.o ads1115.o music.o -o main -lwiringPi

main.o: main.c
	gcc -c main.c -o main.o -lwiringPi

music.o: music.c music.h
	gcc -c music.c -o music.o

stepper.o: stepper.c stepper.h
	gcc -c stepper.c -o stepper.o -lwiringPi

ads1115.o: ads1115.c ads1115.h
	gcc -c ads1115.c -o ads1115.o

clean:
	rm -rf main.o ads1115.o stepper.o music.o main
