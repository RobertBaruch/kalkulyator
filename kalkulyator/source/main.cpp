using namespace std;

#include <cstddef>
#include <new>
#include "Kalkulyator.h"

// Prevents dynamic allocation.
void *operator_new_blocker();  // undefined on purpose to cause link error on dynamic allocs.
void* operator new(std::size_t) throw (std::bad_alloc) {
  return operator_new_blocker();
}

int main(void) {
  kalk::Kalkulyator::instance().run();

  for (;;) { /* Infinite loop to avoid leaving the main function */
    __asm("NOP");
    /* something to use as a breakpoint stop while looping */
  }
}
