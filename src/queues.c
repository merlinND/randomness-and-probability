#include "queues.h"

#include <stdio.h>
#include "distributions.h"

queue_t mm1Queue(double lambda, double mu, double duration) {
	// Init
	double t = 0;
	queue_t sim;
	sim.arrivalsSize = 0;
	sim.departuresSize = 0;

	init_distributions();

	// Arrivals
	while (t < duration && sim.arrivalsSize < MAX_QUEUE_SIZE) {
		t += next_exponential_value(lambda);
		sim.arrivals[sim.arrivalsSize] = t;
		sim.arrivalsSize++;
	}

	// Departures
	if (sim.arrivalsSize > 0) {

		// The first client doesn't have to wait
		t = sim.arrivals[0];
		t += next_exponential_value(mu);
		sim.departures[sim.departuresSize] = t;
		sim.departuresSize++;

		while (t < duration && sim.departuresSize < sim.arrivalsSize - 1) {
			// Someone arrived while the previous person was being served
			if (sim.arrivals[sim.departuresSize - 1] < sim.departures[sim.departuresSize - 1])
				t += next_exponential_value(mu);
			// Someone arrived and could be served immediately
			else
				t = sim.arrivals[sim.departuresSize] + next_exponential_value(mu);

			sim.departures[sim.departuresSize] = t;
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
>>>>>>> FETCH_HEAD
