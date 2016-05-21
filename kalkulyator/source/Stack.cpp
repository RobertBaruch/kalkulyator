/*
 * Stack.cpp
 *
 *  Created on: Mar 27, 2016
 *      Author: rober
 */

#include "Stack.h"

namespace kalk {

Stack& Stack::instance() {
  static Stack instance;
  return instance;
}

void sin() {
  mpfr_ptr top_of_stack = peek();
  mpfr_sin(top_of_stack, top_of_stack, MPFR_RNDN);
}

void cos() {
  mpfr_ptr top_of_stack = peek();
  mpfr_cos(top_of_stack, top_of_stack, MPFR_RNDN);
}

void tan() {
  mpfr_ptr top_of_stack = peek();
  mpfr_tan(top_of_stack, top_of_stack, MPFR_RNDN);
}

void arcsin() {
  mpfr_ptr top_of_stack = peek();
  mpfr_asin(top_of_stack, top_of_stack, MPFR_RNDN);
}

void arccos() {
  mpfr_ptr top_of_stack = peek();
  mpfr_acos(top_of_stack, top_of_stack, MPFR_RNDN);
}

void arctan() {
  mpfr_ptr top_of_stack = peek();
  mpfr_atan(top_of_stack, top_of_stack, MPFR_RNDN);
}

void add() {
  Mpfr x(Stack::instance().pop());
  mpfr_ptr top_of_stack = peek();
  mpfr_add(top_of_stack, top_of_stack, mpfr_ptr(x), MPFR_RNDN);
}

void sub() {
  Mpfr x(Stack::instance().pop());
  mpfr_ptr top_of_stack = peek();
  mpfr_sub(top_of_stack, top_of_stack, mpfr_ptr(x), MPFR_RNDN);
}

void mul() {
  Mpfr x(Stack::instance().pop());
  mpfr_ptr top_of_stack = peek();
  mpfr_mul(top_of_stack, top_of_stack, mpfr_ptr(x), MPFR_RNDN);
}

void div() {
  Mpfr x(Stack::instance().pop());
  mpfr_ptr top_of_stack = peek();
  mpfr_div(top_of_stack, top_of_stack, mpfr_ptr(x), MPFR_RNDN);
}

void sqr() {
  mpfr_ptr top_of_stack = peek();
  mpfr_sqr(top_of_stack, top_of_stack, MPFR_RNDN);
}

void sqrt() {
  mpfr_ptr top_of_stack = peek();
  mpfr_sqrt(top_of_stack, top_of_stack, MPFR_RNDN);
}

void push(const mpfr_t x) {
  Stack::instance().push(x);
}

void push(const char *str) {
  Mpfr value(str);
  Stack::instance().push(mpfr_ptr(value));
}

void push_pi() {
  Mpfr value;
  mpfr_const_pi(mpfr_ptr(value), MPFR_RNDN);
  Stack::instance().push(mpfr_ptr(value));
}

mpfr_ptr peek() {
  return Stack::instance().peek();
}

mpfr_ptr peek_at(int level) {
  return Stack::instance().peek_at(level);
}

Mpfr pop() {
  return Mpfr(Stack::instance().pop());
}

void dup() {
  push(peek());
}

void str_of_stack(char *str, int level) {
  str_of_num(str, Stack::instance().peek_at(level));
}

void str_of_num(char *str, const mpfr_t x) {
  mpfr_exp_t ex;
  mpfr_get_str(str, &ex, 10, 200, x, MPFR_RNDN);
  mpfr_exp_t ex2;
  ex2 = ex;
}

} /* namespace kalk */
