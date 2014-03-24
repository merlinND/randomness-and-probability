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

/* Run a simulation in which:
 * - <meanArrival> clients arrive per hour on average
 * - <meanDeparture> clients leave per hour on average
 * - simulation runs for <duration> minutes
 * And print every relevant information.
 */
void run_simulation(int meanArrival, int meanDeparture, int duration) {
  printf(" - MM1 %d arrivals/hour, %d departures/hour during %d minutes\n", meanArrival, meanDeparture, duration);

  double lambda = (meanArrival / 60.);
  double mu = (meanDeparture / 60.);
  queue_t q = mm1_queue(lambda, mu, duration);

  history_t h = make_history(&q);
  history_to_csv(&h);

  printf("Mean clients number: %f\n", mean_clients_number(&h));
  printf("Mean waiting time: %f\n", mean_waiting_time(&q));
}

int main() {
  run_simulation(12, 20, 180);
  printf("\n\n");
  run_simulation(18, 20, 180);
  printf("\n\n");
  run_simulation(25, 20, 180);
}
