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

history_t make_history(queue_t const * q);
double mean_clients_number(history_t const * h);
double mean_waiting_time(queue_t const * q);

void history_to_csv(history_t const * history);

#endif
