/*
 * Gmp.h
 *
 *  Created on: Mar 27, 2016
 *      Author: rober
 */

#ifndef SOURCE_GMP_MEMORY_H_
#define SOURCE_GMP_MEMORY_H_

#include <gmp.h>
#include <cstddef>
#include <cstring>
#include "Stack.h"

namespace kalk {

class GmpMemory {
 private:
  static constexpr std::size_t kNumSlots = 16 + 2 + Stack::getStackSize();
  // The size of a slot in bytes. It must be enough to hold a 665-bit precision number, plus a few.
  static constexpr std::size_t kSlotSizeBytes = 8 + ((Stack::getPrecision() - 1) / 32 + 1) * sizeof(mp_limb_t);
  static constexpr std::size_t kLargeSlotSizeBytes = 8 * kSlotSizeBytes;
  static constexpr std::size_t kNumLargeSlots = 16;

  // Allocates a slot.
  static void *alloc(std::size_t size) {
    return instance().alloc_impl(size);
  }

  // Frees a slot.
  static void free(void *ptr, std::size_t size) {
    instance().free_impl(ptr, size);
  }

  // Reallocates a slot.
  static void *realloc(void *ptr, std::size_t old_size, std::size_t new_size) {
    void *data = alloc(new_size);
    std::memcpy(data, ptr, old_size);
    free(ptr, old_size);
    return data;
  }

  struct AllocDescriptor_ {
    char data[kSlotSizeBytes];
    bool allocated = false;
  };

  struct LargeAllocDescriptor_ {
    char data[kLargeSlotSizeBytes];
    bool allocated = false;
  };

  // The fixed memory segments.
  AllocDescriptor_ descriptors_[kNumSlots];
  int slots_allocated_ = 0;
  LargeAllocDescriptor_ large_descriptors_[kNumLargeSlots];
  int large_slots_allocated_ = 0;

  GmpMemory();

  // Allocates a slot.
  void *alloc_impl(std::size_t size);

  // Frees a slot.
  void free_impl(void *ptr, std::size_t size);

 public:
  static GmpMemory& instance();

  GmpMemory(GmpMemory&&) = delete;
  GmpMemory(const GmpMemory&) = delete;
  void operator=(GmpMemory&&) = delete;
  void operator=(const GmpMemory&) = delete;
};

} /* namespace kalk */

#endif /* SOURCE_GMP_MEMORY_H_ */
