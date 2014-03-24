#include "queues.h"

int main() {
  queue_t q = mm1Queue(12/60., 20/60., 3*60);
  queue_to_csv(q);
}
