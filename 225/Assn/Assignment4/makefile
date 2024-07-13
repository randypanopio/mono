all: tdQ tdBH

tdQ: testDriver_Q.o Queue.h Event.o EmptyDataCollectionException.o
	g++ -o tdQ -Wall testDriver_Q.o Event.o EmptyDataCollectionException.o

tdBH: testDriver_BH.o BinaryHeap.h Event.o EmptyDataCollectionException.o
	g++ -o tdBH -Wall testDriver_BH.o Event.o EmptyDataCollectionException.o

testDriver_Q.o: testDriver_Q.cpp Queue.h
	g++ -c -Wall testDriver_Q.cpp

testDriver_BH.o: testDriver_BH.cpp BinaryHeap.h
	g++ -c -Wall testDriver_BH.cpp

Event.o: Event.cpp Event.h
	g++ -c -Wall Event.cpp

EmptyDataCollectionException.o: EmptyDataCollectionException.cpp EmptyDataCollectionException.h 
	g++ -c -Wall EmptyDataCollectionException.cpp

clean:	
	rm -f tdQ tdBH *.o
