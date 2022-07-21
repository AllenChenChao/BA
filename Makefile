a.out: test.o sampen.o
	g++ test.o sampen.o -o a.out
test.o: sampen_test.cpp
	g++ -c sampen_test.cpp -o test.o
sampen.o: sampen.cpp
	g++ -c sampen.cpp -o sampen.o

.PHONY:clean
clean:
	-rm -rf *.o

RUN:run
run:
	./a.out