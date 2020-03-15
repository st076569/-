all: st076569_10

st076569_10: functions.o st076569_10.o
	g++ functions.o st076569_10.o -o st076569_10

functions.o: 
	g++ -c ./source/functions.cpp -I ./headers

st076569_10.o:
	g++ -c ./source/st076569_10.cpp -I ./headers

clean:
	rm -f *.o

