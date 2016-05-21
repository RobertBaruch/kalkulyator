/*
 * Stack.h
 *
 *  Created on: Mar 27, 2016
 *      Author: rober
 */

#ifndef STACK_H_
#define STACK_H_

#include <cstddef>
#include <cstdint>
#include <mpfr.h>

namespace kalk {

// A resource management version of mpfr_t.
class Mpfr {
 private:
  mpfr_t data_;

 public:
  Mpfr() {
    mpfr_init(data_);
  }

  explicit Mpfr(const mpfr_t data) {
    mpfr_init_set(data_, data, MPFR_RNDN);
  }

  explicit Mpfr(const char *str) {
    mpfr_init_set_str(data_, str, 10, MPFR_RNDN);
  }

  ~Mpfr() {
    mpfr_clear(data_);
  }

  explicit operator mpfr_ptr() {
    return data_;
  }
};

// The fun stuff. These are functions that use the (singleton) Stack.
extern void push(const mpfr_t);
extern void push(const char *);
extern void push_pi();
extern mpfr_ptr peek();
extern mpfr_ptr peek_at(int level);
extern Mpfr pop();
extern void dup();
extern void str_of_stack(char *str, int level);
extern void str_of_num(char *str, const mpfr_t);

extern void add();
extern void sub();
extern void mul();
extern void div();
extern void sqr();
extern void sqrt();
extern void sin();
extern void cos();
extern void tan();
extern void arcsin();
extern void arccos();
extern void arctan();

class Stack {
 private:
  static constexpr std::size_t kStackSize = 50;
  static constexpr std::size_t kPrecision = 665;

  mpfr_t stack_[kStackSize];
  int8_t stack_size_ = 0;

  Stack() {
    mpfr_set_default_prec(kPrecision);
    mpfr_set_default_rounding_mode(MPFR_RNDN);
  }

 public:
  static Stack& instance();
  static constexpr std::size_t getStackSize() { return kStackSize; }
  static constexpr std::size_t getPrecision() { return kPrecision; }

  void push(const mpfr_t x) {
    mpfr_init_set(stack_[stack_size_], x, MPFR_RNDN);
    ++stack_size_;
  }

  void pop(mpfr_t x) {
    --stack_size_;
    mpfr_init_set(x, stack_[stack_size_], MPFR_RNDN);
    mpfr_clear(stack_[stack_size_]);
  }

  Mpfr pop() {
    --stack_size_;
    Mpfr x(stack_[stack_size_]);
    mpfr_clear(stack_[stack_size_]);
    return x;
  }

  void drop() {
    --stack_size_;
    mpfr_clear(stack_[stack_size_]);
  }

  mpfr_ptr peek() {
    return stack_[stack_size_ - 1];
  }

  mpfr_ptr peek_at(int level) {
    return stack_[stack_size_ - 1 - level];
  }

  int8_t get_stack_size() const {
    return stack_size_;
  }

  Stack(Stack&&) = delete;
  Stack(const Stack&) = delete;
  void operator=(Stack&&) = delete;
  void operator=(const Stack&) = delete;
};

} /* namespace kalk */

#endif /* STACK_H_ */
