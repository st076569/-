all: st076569_14

st076569_14: functions.o st076569_14.o
	g++ functions.o st076569_14.o -o st076569_14

functions.o: 
	g++ -c ./source/functions.cpp -I ./headers

st076569_14.o:
	g++ -c ./source/st076569_14.cpp -I ./headers

clean:
	rm -f *.o

