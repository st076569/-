all: st076569_8

st076569_8: functions.o st076569_8.o
	g++ functions.o st076569_8.o -o st076569_8

functions.o: 
	g++ -c ./source/functions.cpp -I ./headers

st076569_8.o:
	g++ -c ./source/st076569_8.cpp -I ./headers

clean:
	rm -f *.o

