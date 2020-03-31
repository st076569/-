all: st076569_13

st076569_13: functions.o st076569_13.o
	g++ functions.o st076569_13.o -o st076569_13

functions.o: 
	g++ -c ./source/functions.cpp -I ./headers

st076569_13.o:
	g++ -c ./source/st076569_13.cpp -I ./headers

clean:
	rm -f *.o

