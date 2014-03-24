#include "queues.h"

#include <stdio.h>

int main() {
  printf(" - MM1 12 arrivals/hour, 20 departures/hour during 3 hours\n");
  queue_t q = mm1Queue(12/60., 20/60., 3*60);
  queue_to_csv(q);

  printf("\n\n");

  printf(" - MM1 18 arrivals/hour, 20 departures/hour during 3 hours\n");
  q = mm1Queue(18/60., 20/60., 3*60);
  queue_to_csv(q);
}
