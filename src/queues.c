#include "queues.h"

#include <stdio.h>
#include "distributions.h"

queue_t mm1_queue(double lambda, double mu, double duration) {
  // Init
  double t = 0., out = 0.;
  queue_t sim;
  sim.arrivalsSize = 0;
  sim.departuresSize = 0;

  init_distributions();

  // Run the simulation in time
  while (t < duration && sim.arrivalsSize < MAX_QUEUE_SIZE) {
    t += next_exponential_value(lambda);

    if (t < duration) {
      sim.arrivals[sim.arrivalsSize] = t;
      sim.arrivalsSize++;

      // This person arrived and could be served immediately
      if (sim.arrivalsSize <= 1 || t >= sim.departures[sim.departuresSize - 1])
        out = t + next_exponential_value(mu);
      // This person arrived but someone else was being served
      else
        out = sim.departures[sim.departuresSize - 1] + next_exponential_value(mu);

      if (out < duration) {
        sim.departures[sim.departuresSize] = out;
        sim.departuresSize++;
      }
    }
  }

  return sim;
}

history_t make_history(queue_t const * q) {
  history_t history;
  history.size = 0;

  int count = 0;
  int itArrivals = 0;
  int itDepartures = 0;
  while(itArrivals < q->arrivalsSize || itDepartures < q->departuresSize) {
    if((itArrivals < q->arrivalsSize && q->arrivals[itArrivals] <=
        q->departures[itDepartures]) || itDepartures >=  q->departuresSize) {
      count++;
      history.points[history.size].t = q->arrivals[itArrivals];
      history.points[history.size].n = count;
      itArrivals++;
    } else {
      count--;
      history.points[history.size].t = q->departures[itDepartures];
      history.points[history.size].n = count;
      itDepartures++;
    }
    history.size++;
  }

  return history;
}

double mean_clients_number(history_t const * h) {
  // Weighted sum (a given number of client for a given time)
  double sum = 0, dt;
  for (int i = 1; i < h->size; ++i) {
    dt = (h->points[i].t - h->points[i - 1].t);
    sum += (dt * h->points[i - 1].n);
  }

  double total = (h->points[h->size - 1].t - h->points[0].t);
  return (sum / total);
}

// Actual waiting time = time in queue + time being served
double mean_waiting_time(queue_t const * q) {
  double sum = 0;
  for (int i = 0; i < q->departuresSize; ++i) {
    sum += (q->departures[i] - (double)q->arrivals[i]);
  }
  return (sum / q->departuresSize);
}
