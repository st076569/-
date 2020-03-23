all: st076569_11

st076569_11: functions.o st076569_11.o
	g++ functions.o st076569_11.o -o st076569_11

functions.o: 
	g++ -c ./source/functions.cpp -I ./headers

st076569_11.o:
	g++ -c ./source/st076569_11.cpp -I ./headers

clean:
	rm -f *.o

