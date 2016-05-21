/*
 * Gmp.cpp
 *
 *  Created on: Mar 27, 2016
 *      Author: rober
 */

#include "GmpMemory.h"
#include <gmp.h>
#include <cstdint>
#include <cstdlib>
#include "DebugMessages.h"

namespace kalk {

GmpMemory& GmpMemory::instance() {
  static GmpMemory instance;
  return instance;
}

GmpMemory::GmpMemory() {
  mp_set_memory_functions(alloc, realloc, free);
}

void *GmpMemory::alloc_impl(std::size_t size) {
  if (size > kLargeSlotSizeBytes) {
    panic("Attempted alloc %d bytes > max size %d\n", size, kLargeSlotSizeBytes);
  }

  if (size <= kSlotSizeBytes) {
    AllocDescriptor_ *descriptor = descriptors_;
    for (uint8_t slot = 0; slot < kNumSlots; slot++, descriptor++) {
      if (!descriptor->allocated) {
        descriptor->allocated = true;
        ++slots_allocated_;
        return static_cast<void*>(descriptor);
      }
    }
  }

  LargeAllocDescriptor_ *large_descriptor = large_descriptors_;
  for (uint8_t slot = 0; slot < kNumLargeSlots; slot++, large_descriptor++) {
    if (!large_descriptor->allocated) {
      large_descriptor->allocated = true;
      ++large_slots_allocated_;
      return static_cast<void*>(large_descriptor);
    }
  }

  panic("Attempted alloc %d bytes but no slots left\n", size);
}

void GmpMemory::free_impl(void *ptr, std::size_t size) {
  AllocDescriptor_ *descriptor = descriptors_;
  for (uint8_t slot = 0; slot < kNumSlots; slot++, descriptor++) {
    if (ptr == static_cast<void*>(descriptor)) {
      if (!descriptor->allocated) {
        panic("Double free of %d bytes at %p\n", size, ptr);
      }
      --slots_allocated_;
      descriptor->allocated = false;
      return;
    }
  }

  LargeAllocDescriptor_ *large_descriptor = large_descriptors_;
  for (uint8_t slot = 0; slot < kNumLargeSlots; slot++, large_descriptor++) {
    if (ptr == static_cast<void*>(large_descriptor)) {
      if (!large_descriptor->allocated) {
        panic("Double free of %d bytes at %p\n", size, ptr);
      }
      --large_slots_allocated_;
      large_descriptor->allocated = false;
      return;
    }
  }

  panic("Free of %d bytes at unallocated %p\n", size, ptr);
}
} /* namespace kalk */
