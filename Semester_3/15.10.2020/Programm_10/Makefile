st076569_4: managerlib.o st076569_10.o
	g++ managerlib.o st076569_10.o -o st076569_10 -lpthread

managerlib.o: 
	g++ -c ./source/managerlib.cpp -I ./headers

st076569_10.o:
	g++ -c ./source/st076569_10.cpp -I ./headers

clean:
	rm -f *.o

