#include "queues.h"

#include <stdio.h>

void history_to_csv(history_t const * history) {
  printf("Timestamp,Number\n");

  data_point_t point;
  for (int i = 0; i < history->size; ++i) {
    point = history->points[i];
    printf("%f,%d\n", point.t, point.n);
  }
}

/* Run an M/M/n simulation in which:
 * - <n> servers are available to handle clients
 * - <meanArrival> clients arrive per hour on average
 * - <meanDeparture> clients leave per hour on average
 * - simulation runs for <duration> minutes
 * And print every relevant information.
 */
void run_simulation(int n, int meanArrival, int meanDeparture, int duration) {
  printf("-- M/M/%d %d arrivals/hour, %d departures/hour during %d minutes --\n", n, meanArrival, meanDeparture, duration);

  double lambda = (meanArrival / 60.);
  double mu = n * (meanDeparture / 60.);
  queue_t q = mm1_queue(lambda, mu, duration);

  history_t h = make_history(&q);
  printf("Mean clients number: %f\n", mean_clients_number(&h));
  printf("Mean waiting time: %f\n", mean_waiting_time(&q));

  history_to_csv(&h);
}

int main() {
  run_simulation(1, 12, 20, 180);
  printf("\n\n");
  run_simulation(1, 18, 20, 180);
  printf("\n\n");
  run_simulation(2, 12, 20, 180);
}
