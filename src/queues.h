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
typedef struct queue_t queue_t;

void queue_to_csv(queue_t q);

#endif
