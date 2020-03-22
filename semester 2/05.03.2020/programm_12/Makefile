all: st076569_12

st076569_12: functions.o st076569_12.o
	g++ functions.o st076569_12.o -o st076569_12

functions.o: 
	g++ -c ./source/functions.cpp -I ./headers

st076569_12.o:
	g++ -c ./source/st076569_12.cpp -I ./headers

clean:
	rm -f *.o

