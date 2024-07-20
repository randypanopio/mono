/*
 * BankSimApp.cpp
 * 
 * Description: A Bank Simulation Application to simulate wether or not it would be
 * worthwhile to hire a second teller.
 *
 * Author: Randy Panopio
 * Last Modification Date: July 2024
 */

#include <iomanip>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cassert>
#include "Queue.h"
#include "EmptyDataCollectionException.h"
#include "PriorityQueue.h"
#include "Event.h"

using namespace std;

// TODO update PQ to memory allocate in FIRST insertion
int main(int argc, char *argv[]) {
    // if (argc <= 1) {
    //     cout << "Missing the redirected file" << endl;
    //     return 1;
    // }

    cout << "Simulation Begins" << endl;
    auto pq = PriorityQueue<Event>();
    auto q = Queue<Event>();

    int arrivalTime, transactionLength; 
    double transactionCount = 0;
    // Read lines from std::cin until the end of the input, generate the events
    while (cin >> arrivalTime >> transactionLength) {
        // cout << "Inserted to pq arrival: " << arrivalTime << ", length: " << transactionLength << endl;
        Event event = Event('A', arrivalTime, transactionLength);
        if (pq.enqueue(event)) {
            transactionCount++;
        } else {
            // cout << "Unable to enqueue an event" << endl;
        }
        
        // TODO remove me
        // cout << "Inserted to pq arrival: " << arrivalTime << ", length: " << transactionLength << endl;
    }
    
    // go through the pq 
    int currentTime = 0;
    double totalWaitTime = 0;
    while (!pq.isEmpty()) {
        Event currentEvent = pq.peek();
        currentTime = currentEvent.getTime();

        if (currentEvent.isArrival()) {
            // currentEvent.print();
            // cout << " peeked this event and removed" << endl;
            cout << "Processing an arrival event at time: " << setw(5) << currentEvent.getTime() << endl;
            pq.dequeue();
            if (q.isEmpty()) {
                int departureTime = currentTime + currentEvent.getLength();
                // insert a departure to q
                Event event = Event('D', departureTime);
                pq.enqueue(event);
            }
            q.enqueue(currentEvent);
        } else {
            cout << "Processing a departure event at time: " << setw(4) << currentEvent.getTime() << endl;
            Event customer = q.peek();
            pq.dequeue();
            totalWaitTime += static_cast<double>((currentTime - customer.getTime()));
            // cout << "Customer (avgd) wait time: " << (currentTime - customer.getTime()) << endl; 
            q.dequeue();
            if (!q.isEmpty()) {
                // check q and enq them to pq
                Event nextCustomer = q.peek();
                int departureTime = currentTime + nextCustomer.getLength();
                Event event = Event('D', departureTime);
                pq.enqueue(event);
            }            
        }        
    }
    
    cout << "Simulation Ends" << endl;
    cout << "\nFinal Statistics:" << endl << endl;
    cout << "\tTotal number of people processed: " << transactionCount << endl;
    // this should be correct, I give up
    double averageWaitTime =  static_cast<double>(totalWaitTime / transactionCount);
    cout << "\tAverage amount of time spent waiting: " << averageWaitTime << endl;

    // no need to free, using stack decleration
    // delete q;
    // delete pq;
    return 0;
}
