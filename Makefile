.PHONY: clean

all: stepper-test sensor-test

stepper-test: stepperTest.o
	gcc stepperTest.o -o stepperTest -lwiringPi

stepperTest.o: stepperTest.c
	gcc -c stepperTest.c -o stepperTest.o -lwiringPi

sensor-test: test.o ads1115.o
	gcc test.o ads1115.o -o test

test.o: test.c
	gcc -c test.c -o test.o

ads1115.o: ads1115.c
	gcc -c ads1115.c -o ads1115.o

clean:
	rm -rf test.o stepperTest.o ads1115.o test stepperTest
