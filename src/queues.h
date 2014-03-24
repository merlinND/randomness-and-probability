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

queue_t mm1Queue(double lambda, double mu, double duration);
struct data_point_t {
  double t;
  int n;
};
typedef struct data_point_t data_point_t;

struct history_t {
  int size;
  data_point_t points[MAX_QUEUE_SIZE * 2];
};
typedef struct history_t history_t;

queue_t mm1_queue(double lambda, double mu, double duration);

void queue_to_csv(queue_t q);
history_t make_history(queue_t const * q);

#endif
