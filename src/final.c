#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include "tests.h"
#include "queues.h"

#define MAX_TRIES 20
#define ARRAY_MAX_SIZE 1024

#define CSV_HEADER "Oldrand 4 MSBs,Oldrand 4 LSBs,Von-Neumann,Mesrene-Twister,AES\n"

/* Run a simulation in which:
 * - <meanArrival> clients arrive per hour on average
 * - <meanDeparture> clients leave per hour on average
 * - simulation runs for <duration> minutes
 * And print every relevant information.
 */
void run_simulation(int meanArrival, int meanDeparture, int duration) {
  printf("### %d arrivals/hour, %d departures/hour during %d minutes\n\n", meanArrival, meanDeparture, duration);

  double lambda = (meanArrival / 60.);
  double mu = (meanDeparture / 60.);
  queue_t q = mm1_queue(lambda, mu, duration);

  printf("#### Arrival & Departure times\n\n");

  printf("##### Arrival times\n\n");

  for(int i = 1; i <= q.arrivalsSize; i ++) {
    printf("%d. %f minutes\n", i, q.arrivals[i - 1]);
  }
  printf("\n");

  printf("##### Departure times\n\n");

  for(int i = 1; i <= q.departuresSize; i ++) {
    printf("%d. %f minutes\n", i, q.departures[i - 1]);
  }
  printf("\n");

  printf("#### Queue evolution\n\n");

  history_t h = make_history(&q);

  printf("```\n");
  history_to_csv(&h);
  printf("```\n\n");

  printf("#### Statistics\n\n");

  printf(" - Mean clients number: %f\n", mean_clients_number(&h));
  printf(" - Mean waiting time: %f\n\n", mean_waiting_time(&q));
}

int main()
{
  printf("# Random Number Generation & Probability Distributions\n\n");

  printf("## Random Number Testing\n\n");
  autoseed_old_c_rand();
  autoseed_aes();
  autoseed_von_neumann();
  autoseed_mesrene_twister();
  for(int i = 1; i <= MAX_TRIES; i ++) {
    word32 generated_rand_upper[ARRAY_MAX_SIZE],
          generated_rand_lower[ARRAY_MAX_SIZE],
          generated_VN[ARRAY_MAX_SIZE],
          generated_MT[ARRAY_MAX_SIZE],
          generated_AES[ARRAY_MAX_SIZE];

    printf("### Try %d\n\n", i);

    printf("#### %d generated numbers\n\n", ARRAY_MAX_SIZE);
    printf("```\n");
    printf(CSV_HEADER);
    for(int j = 0; j < ARRAY_MAX_SIZE; j ++) {
      int output_rand = autonext_old_c_rand();
      generated_rand_upper[j] = (word32) msb(output_rand);
      generated_rand_lower[j] = (word32) lsb(output_rand);
      generated_VN[j] = (word32) autonext_von_neumann(); // Von Neumann
      generated_MT[j] = (word32) autonext_mesrene_twister(); // Mersenne-Twister
      generated_AES[j] = (word32) autonext_aes(); // AES

      printf("%u,", generated_rand_upper[j]);
      printf("%u,", generated_rand_lower[j]);
      printf("%u,", generated_VN[j]);
      printf("%u,", generated_MT[j]);
      printf("%u\n",generated_AES[j]);
    }
    printf("```\n\n");

    printf("#### Monobit Frequency Test\n\n");

    printf(" - Old C Rand 4 MSBs: %f\n", frequency(ARRAY_MAX_SIZE, 4, generated_rand_upper));
    printf(" - Old C Rand 4 LSBs: %f\n", frequency(ARRAY_MAX_SIZE, 4, generated_rand_lower));
    printf(" - Von Neumann: %f\n", frequency(ARRAY_MAX_SIZE, 4, generated_VN));
    printf(" - Mesrene Twister: %f\n", frequency(ARRAY_MAX_SIZE, 4, generated_MT));
    printf(" - AES: %f\n\n", frequency(ARRAY_MAX_SIZE, 4, generated_AES));

    printf("#### Runs Length Test\n\n");

    printf(" - Old C Rand 4 MSBs: %f\n", run_length(ARRAY_MAX_SIZE, 4, generated_rand_upper));
    printf(" - Old C Rand 4 LSBs: %f\n", run_length(ARRAY_MAX_SIZE, 4, generated_rand_lower));
    printf(" - Von Neumann: %f\n", run_length(ARRAY_MAX_SIZE, 4, generated_VN));
    printf(" - Mesrene Twister: %f\n", run_length(ARRAY_MAX_SIZE, 4, generated_MT));
    printf(" - AES: %f\n\n", run_length(ARRAY_MAX_SIZE, 4, generated_AES));
  }

  printf("## M/M/1 queue system\n\n");

  run_simulation(12, 20, 180);

  run_simulation(24, 20, 180);

  return 0;
}
