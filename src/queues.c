#include "queues.h"

#include <stdio.h>
#include "distributions.h"

queue_t mm1Queue(double lambda, double mu, double duration) {
	// Init
	double t, out = 0;
	queue_t sim;
	sim.arrivalsSize = 0;
	sim.departuresSize = 0;

	init_distributions();

	// Run the simulation in time
	while (t < duration && sim.arrivalsSize < MAX_QUEUE_SIZE) {
		t += next_exponential_value(lambda);
		sim.arrivals[sim.arrivalsSize] = t;
		sim.arrivalsSize++;


		// This person arrived and could be served immediately
		if (sim.arrivalsSize <= 1 || sim.arrivals[sim.departuresSize - 1] >= sim.departures[sim.departuresSize - 1]) {
			out = t + next_exponential_value(mu);
		}
		// This person arrived but someone else was being served
		else {
			out = sim.departures[sim.departuresSize - 1] + next_exponential_value(mu);
		}
		if (out < duration) {
			sim.departures[sim.departuresSize] = out;
			sim.departuresSize++;
		}
	}

	return sim;
}

void queue_to_csv(queue_t q) {
  printf("Timestamp,Number\n");
  int count = 0;
  int itArrivals = 0;
  int itDepartures = 0;
  while(itArrivals < q.arrivalsSize || itDepartures < q.departuresSize) {
    if((itArrivals < q.arrivalsSize && q.arrivals[itArrivals] <=
        q.departures[itDepartures]) || itDepartures >=  q.departuresSize) {
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
