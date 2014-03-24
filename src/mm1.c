#include "queues.h"

int main() {
  queue_t q = mm1Queue(1/(double)12, 1/(double)20, 3*60);
  queue_to_csv(q);
}
