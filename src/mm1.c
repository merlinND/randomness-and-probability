#include "queues.h"

#include <stdio.h>

int main() {
  printf(" - MM1 12 arrivals/hour, 20 departures/hour during 3 hours\n");
  queue_t q = mm1Queue(12/60., 20/60., 3*60);
  queue_to_csv(q);
void history_to_csv(history_t const * history) {
  printf("Timestamp,Number\n");

  printf("\n\n");
  data_point_t point;
  for (int i = 0; i < history->size; ++i) {
    point = history->points[i];
    printf("%f,%d\n", point.t, point.n);
  }
}

  printf(" - MM1 18 arrivals/hour, 20 departures/hour during 3 hours\n");
  q = mm1Queue(18/60., 20/60., 3*60);
  queue_to_csv(q);
}
