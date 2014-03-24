#ifndef QUEUES_H
#define QUEUES_H

#define MAX_QUEUE_SIZE 1000

struct queue_t {
	int arrivalsSize;
	// Times of arrivals
	double arrivals[MAX_QUEUE_SIZE];
	int departuresSize;
	// Times of departures
	double departures[MAX_QUEUE_SIZE];
};
typedef queue_t queue_t;

#endif
