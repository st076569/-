all: st076569_9

st076569_9: functions.o st076569_9.o
	g++ functions.o st076569_9.o -o st076569_9

functions.o: 
	g++ -c ./source/functions.cpp -I ./headers

st076569_9.o:
	g++ -c ./source/st076569_9.cpp -I ./headers

clean:
	rm -f *.o

