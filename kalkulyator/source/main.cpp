using namespace std;

#include <cstddef>
#include <new>
#include "Kalkulyator.h"

// Prevents dynamic allocation.
/**
 * Undefined on purpose to cause link error on dynamic allocations.
 */
void *operator_new_blocker();

/**
 * Calls an undefined function on purpose to cause link error on dynamic allications.
 */
void* operator new(std::size_t) throw (std::bad_alloc) {
  return operator_new_blocker();
}

/**
 * The main program. All it does is get a singleton Kalkulyator instance and run it. If it
 * returns, we just spin-loop.
 */
int main(void) {
  kalk::Kalkulyator::instance().run();

  for (;;) { /* Infinite loop to avoid leaving the main function */
    __asm("NOP");
    /* something to use as a breakpoint stop while looping */
  }
}
