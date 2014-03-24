#include "queues.h"

#include <stdio.h>

void queue_to_csv(queue_t q) {
  printf("Timestamp,Number\n");
  int count = 0;
  int itArrivals = 0;
  int itDepartures = 0;
  while(itArrivals < q.arrivalsSize || itDepartures < q.departuresSize) {
    if(itArrivals < q.arrivalsSize && q.arrivals[itArrivals] <=
        q.departures[itDepartures]) {
      count ++;
      printf("%f,%d\n", q.arrivals[itArrivals], count);
      itArrivals ++;
    } else {
      count --;
      printf("%f,%d\n", q.departures[itDepartures], count);
      itDepartures ++;
    }
  }
}
