.PHONY: clean

all: main stepper-test sensor-test

main: main.o stepper.o ads1115.o music.o
	gcc main.o stepper.o ads1115.o music.o -o main -lwiringPi

main.o: main.c
	gcc -c main.c -o main.o -lwiringPi

music.o: music.c music.h
	gcc -c music.c -o music.o

stepper-test: stepperTest.o stepper.o
	gcc stepperTest.o stepper.o -o stepperTest -lwiringPi

stepperTest.o: stepperTest.c
	gcc -c stepperTest.c -o stepperTest.o -lwiringPi

stepper.o: stepper.c stepper.h
	gcc -c stepper.c -o stepper.o -lwiringPi

sensor-test: test.o ads1115.o
	gcc test.o ads1115.o -o test

test.o: test.c
	gcc -c test.c -o test.o

ads1115.o: ads1115.c ads1115.h
	gcc -c ads1115.c -o ads1115.o

clean:
	rm -rf main.o test.o stepperTest.o ads1115.o stepper.o music.o main test stepperTest
