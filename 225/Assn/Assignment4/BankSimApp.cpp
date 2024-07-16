/*
 * BankSimApp.cpp
 * 
 * Description: A Bank Simulation Application to simulate wether or not it would be
 * worthwhile to hire a second teller.
 *
 * Author: Randy Panopio
 * Last Modification Date: July 2024
 */

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include "Queue.h"
#include "EmptyDataCollectionException.h"
#include "PriorityQueue.h"
#include "Event.h"

// Use Event template for simulation, Event will dictate the "priority" of our customers
template class PriorityQueue<Event>;

using namespace std;


// TODO update PQ to memory allocate in FIRST insertion
int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cout << "Missing the data filename!" << endl;
        return 1;
    }

    // read file
    string filename = argv[1];
    ifstream myfile(filename);
    if (!myfile.is_open()) {
        cout << "Unable to open file!" << endl;
        return 1;
    }

    cout << "Simulation Begins" << endl;

    PriorityQueue<Event> pq;
    // Queue<Event> customerQueue;
    int currentTime = 0;
    int totalWaitTime = 0;
    int totalProcessed = 0;
    cout << totalWaitTime << totalProcessed << currentTime<< endl;
    double averageWaitTime = 3.3;

    int arrivalTime, transactionTime;
    while (myfile >> arrivalTime >> transactionTime) {
        Event event = Event(arrivalTime, transactionTime);
        pq.enqueue(event);
        // pq.enqueue(Event(Event::ARRIVAL, arrivalTime, transactionTime));
        // remove me on submission
        cout << "Inserting event to PQ: arrival time:" << arrivalTime << ", transactionTime: " << transactionTime << endl;
    }

    myfile.close();

    

    while (!pq.isEmpty()) {
        Event currentEvent = pq.peek();
        currentTime = currentEvent.getTime();

        // if (currentEvent.isArrival()) {
        //     cout << "Processing an arrival event at time: " << setw(5) << currentEvent.getTime() << endl;
        //     pq.dequeue();
        //     if (customerQueue.empty()) {
        //         int departureTime = currentTime + currentEvent.getLength();
        //         pq.enqueue(Event(Event::DEPARTURE, departureTime));
        //     }
        //     customerQueue.push(currentEvent);
        // } else {
        //     cout << "Processing a departure event at time: " << setw(5) << currentEvent.getTime() << endl;
        //     pq.dequeue();
        //     Event customer = customerQueue.front();
        //     customerQueue.pop();
        //     totalWaitTime += (currentTime - customer.getTime());
        //     totalProcessed++;
        //     if (!customerQueue.empty()) {
        //         Event nextCustomer = customerQueue.front();
        //         int departureTime = currentTime + nextCustomer.getLength();
        //         pq.enqueue(Event(Event::DEPARTURE, departureTime));
        //     }
        // }
    }

    cout << "Simulation Ends" << endl;

    cout << "\nFinal Statistics:\n";
    cout << "\tTotal number of people processed: " << totalProcessed << endl;
    cout << "\tAverage amount of time spent waiting: " << averageWaitTime << endl;

    return 0;
}
