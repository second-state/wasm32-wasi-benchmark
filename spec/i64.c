#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOINLINE __attribute__((noinline))

NOINLINE uint64_t u_add(uint64_t a, uint64_t b) { return a + b; }
NOINLINE uint64_t u_sub(uint64_t a, uint64_t b) { return a - b; }
NOINLINE uint64_t u_mul(uint64_t a, uint64_t b) { return a * b; }
NOINLINE uint64_t u_div(uint64_t a, uint64_t b) { return a / b; }
NOINLINE uint64_t s_div(uint64_t a, uint64_t b) {
  return ((int64_t)a) / ((int64_t)b);
}
NOINLINE uint64_t u_rem(uint64_t a, uint64_t b) { return a % b; }
NOINLINE uint64_t s_rem(uint64_t a, uint64_t b) {
  int64_t x = a;
  int64_t y = b;
#ifndef __wasm32__
  if (x == INT64_MIN && y == -1) {
    return 0;
  }
#endif
  return x % y;
}
NOINLINE uint64_t u_and(uint64_t a, uint64_t b) { return a & b; }
NOINLINE uint64_t u_or(uint64_t a, uint64_t b) { return a | b; }
NOINLINE uint64_t u_xor(uint64_t a, uint64_t b) { return a ^ b; }
NOINLINE uint64_t u_shl(uint64_t a, uint64_t b) { return a << b; }
NOINLINE uint64_t u_shr(uint64_t a, uint64_t b) { return a >> b; }
NOINLINE uint64_t s_shr(uint64_t a, uint64_t b) {
  return ((int64_t)a) >> ((int64_t)b);
}
NOINLINE uint64_t u_rotl(uint64_t a, uint64_t b) {
  return (a << b) | (a >> (sizeof(a) * 8 - b));
}
NOINLINE uint64_t u_rotr(uint64_t a, uint64_t b) {
  return (a >> b) | (a << (sizeof(a) * 8 - b));
}
NOINLINE uint64_t u_clz(uint64_t a) {
  return a == 0 ? sizeof(a) * 8 : __builtin_clzll(a);
}
NOINLINE uint64_t u_ctz(uint64_t a) {
  return a == 0 ? sizeof(a) * 8 : __builtin_ctzll(a);
}
NOINLINE uint64_t u_popcnt(uint64_t a) { return __builtin_popcountll(a); }
NOINLINE uint64_t s_extend8(uint64_t a) {
  int8_t v = a;
  return v;
}
NOINLINE uint64_t s_extend16(uint64_t a) {
  int16_t v = a;
  return v;
}
NOINLINE uint64_t s_extend32(uint64_t a) {
  int32_t v = a;
  return v;
}
NOINLINE bool u_eqz(uint64_t a) { return a == UINT32_C(0); }
NOINLINE bool u_eq(uint64_t a, uint64_t b) { return a == b; }
NOINLINE bool u_ne(uint64_t a, uint64_t b) { return a != b; }
NOINLINE bool u_lt(uint64_t a, uint64_t b) { return a < b; }
NOINLINE bool s_lt(uint64_t a, uint64_t b) {
  return ((int64_t)a) < ((int64_t)b);
}
NOINLINE bool u_le(uint64_t a, uint64_t b) { return a <= b; }
NOINLINE bool s_le(uint64_t a, uint64_t b) {
  return ((int64_t)a) <= ((int64_t)b);
}
NOINLINE bool u_gt(uint64_t a, uint64_t b) { return a > b; }
NOINLINE bool s_gt(uint64_t a, uint64_t b) {
  return ((int64_t)a) > ((int64_t)b);
}
NOINLINE bool u_ge(uint64_t a, uint64_t b) { return a >= b; }
NOINLINE bool s_ge(uint64_t a, uint64_t b) {
  return ((int64_t)a) >= ((int64_t)b);
}

NOINLINE bool eq(uint64_t a, uint64_t b) { return a == b; }

static inline void check1(uint32_t line, uint64_t (*func)(uint64_t), uint64_t a,
                          uint64_t b) {
  const uint64_t x = func(a);
  if (!eq(x, b)) {
    printf("%" PRIu32 " 0x%016" PRIx64 " 0x%016" PRIx64 " 0x%016" PRIx64 "\n",
           line, a, x, b);
  }
}

static inline void check2(uint32_t line, bool (*func)(uint64_t), uint64_t a,
                          bool b) {
  const bool x = func(a);
  if (!eq(x, b)) {
    printf("%" PRIu32 " 0x%016" PRIx64 " 0x%016d 0x%016d\n", line, a, x, b);
  }
}

static inline void check3(uint32_t line, uint64_t (*func)(uint64_t, uint64_t),
                          uint64_t a, uint64_t b, uint64_t c) {
  const uint64_t x = func(a, b);
  if (!eq(x, c)) {
    printf("%" PRIu32 " 0x%016" PRIx64 " 0x%016" PRIx64 " 0x%016" PRIx64
           " 0x%016" PRIx64 "\n",
           line, a, b, x, c);
  }
}

static inline void check4(uint32_t line, bool (*func)(uint64_t, uint64_t),
                          uint64_t a, uint64_t b, bool c) {
  const bool x = func(a, b);
  if (x != c) {
    printf("%" PRIu32 " 0x%016" PRIx64 " 0x%016" PRIx64 " %d %d\n", line, a, b,
           x, c);
  }
}

struct data1 {
  uint32_t line;
  uint64_t (*func)(uint64_t);
  uint64_t v;
  uint64_t r;
};
struct data2 {
  uint32_t line;
  bool (*func)(uint64_t);
  uint64_t v;
  bool r;
};
struct data3 {
  uint32_t line;
  uint64_t (*func)(uint64_t, uint64_t);
  uint64_t v1;
  uint64_t v2;
  uint64_t r;
};
struct data4 {
  uint32_t line;
  bool (*func)(uint64_t, uint64_t);
  uint64_t v1;
  uint64_t v2;
  bool r;
};
int main(int argc, char **argv) {
  static const struct data1 d1[] = {
      {__LINE__, u_clz, UINT64_C(0xffffffffffffffff), UINT64_C(0)},
      {__LINE__, u_clz, UINT64_C(0), UINT64_C(64)},
      {__LINE__, u_clz, UINT64_C(0x8000), UINT64_C(48)},
      {__LINE__, u_clz, UINT64_C(0xff), UINT64_C(56)},
      {__LINE__, u_clz, UINT64_C(0x8000000000000000), UINT64_C(0)},
      {__LINE__, u_clz, UINT64_C(1), UINT64_C(63)},
      {__LINE__, u_clz, UINT64_C(2), UINT64_C(62)},
      {__LINE__, u_clz, UINT64_C(0x7fffffffffffffff), UINT64_C(1)},
      {__LINE__, u_ctz, UINT64_C(-1), UINT64_C(0)},
      {__LINE__, u_ctz, UINT64_C(0), UINT64_C(64)},
      {__LINE__, u_ctz, UINT64_C(0x00008000), UINT64_C(15)},
      {__LINE__, u_ctz, UINT64_C(0x00010000), UINT64_C(16)},
      {__LINE__, u_ctz, UINT64_C(0x8000000000000000), UINT64_C(63)},
      {__LINE__, u_ctz, UINT64_C(0x7fffffffffffffff), UINT64_C(0)},
      {__LINE__, u_popcnt, UINT64_C(-1), UINT64_C(64)},
      {__LINE__, u_popcnt, UINT64_C(0), UINT64_C(0)},
      {__LINE__, u_popcnt, UINT64_C(0x00008000), UINT64_C(1)},
      {__LINE__, u_popcnt, UINT64_C(0x8000800080008000), UINT64_C(4)},
      {__LINE__, u_popcnt, UINT64_C(0x7fffffffffffffff), UINT64_C(63)},
      {__LINE__, u_popcnt, UINT64_C(0xAAAAAAAA55555555), UINT64_C(32)},
      {__LINE__, u_popcnt, UINT64_C(0x99999999AAAAAAAA), UINT64_C(32)},
      {__LINE__, u_popcnt, UINT64_C(0xDEADBEEFDEADBEEF), UINT64_C(48)},
      {__LINE__, s_extend8, INT64_C(0), INT64_C(0)},
      {__LINE__, s_extend8, INT64_C(0x7f), INT64_C(127)},
      {__LINE__, s_extend8, INT64_C(0x80), INT64_C(-128)},
      {__LINE__, s_extend8, INT64_C(0xff), INT64_C(-1)},
      {__LINE__, s_extend8, INT64_C(0x0123456789abcd00), INT64_C(0)},
      {__LINE__, s_extend8, INT64_C(0xfedcba9876543280), INT64_C(-0x80)},
      {__LINE__, s_extend8, INT64_C(-1), INT64_C(-1)},
      {__LINE__, s_extend16, INT64_C(0), INT64_C(0)},
      {__LINE__, s_extend16, INT64_C(0x7fff), INT64_C(32767)},
      {__LINE__, s_extend16, INT64_C(0x8000), INT64_C(-32768)},
      {__LINE__, s_extend16, INT64_C(0xffff), INT64_C(-1)},
      {__LINE__, s_extend16, INT64_C(0x123456789abc0000), INT64_C(0)},
      {__LINE__, s_extend16, INT64_C(0xfedcba9876548000), INT64_C(-0x8000)},
      {__LINE__, s_extend16, INT64_C(-1), INT64_C(-1)},
      {__LINE__, s_extend32, INT64_C(0), INT64_C(0)},
      {__LINE__, s_extend32, INT64_C(0x7fff), INT64_C(32767)},
      {__LINE__, s_extend32, INT64_C(0x8000), INT64_C(32768)},
      {__LINE__, s_extend32, INT64_C(0xffff), INT64_C(65535)},
      {__LINE__, s_extend32, INT64_C(0x7fffffff), INT64_C(0x7fffffff)},
      {__LINE__, s_extend32, INT64_C(0x80000000), INT64_C(-0x80000000)},
      {__LINE__, s_extend32, INT64_C(0xffffffff), INT64_C(-1)},
      {__LINE__, s_extend32, INT64_C(0x0123456700000000), INT64_C(0)},
      {__LINE__, s_extend32, INT64_C(0xfedcba9880000000), INT64_C(-0x80000000)},
      {__LINE__, s_extend32, INT64_C(-1), INT64_C(-1)},
  };
  static const struct data2 d2[] = {
      {__LINE__, u_eqz, UINT64_C(0), true},
      {__LINE__, u_eqz, UINT64_C(1), false},
      {__LINE__, u_eqz, UINT64_C(0x8000000000000000), false},
      {__LINE__, u_eqz, UINT64_C(0x7fffffffffffffff), false},
      {__LINE__, u_eqz, UINT64_C(0xffffffffffffffff), false},
  };
  static const struct data3 d3[] = {
      {__LINE__, u_add, UINT64_C(1), UINT64_C(1), UINT64_C(2)},
      {__LINE__, u_add, UINT64_C(1), UINT64_C(0), UINT64_C(1)},
      {__LINE__, u_add, UINT64_C(-1), UINT64_C(-1), UINT64_C(-2)},
      {__LINE__, u_add, UINT64_C(-1), UINT64_C(1), UINT64_C(0)},
      {__LINE__, u_add, UINT64_C(0x7fffffffffffffff), UINT64_C(1),
       UINT64_C(0x8000000000000000)},
      {__LINE__, u_add, UINT64_C(0x8000000000000000), UINT64_C(-1),
       UINT64_C(0x7fffffffffffffff)},
      {__LINE__, u_add, UINT64_C(0x8000000000000000),
       UINT64_C(0x8000000000000000), UINT64_C(0)},
      {__LINE__, u_add, UINT64_C(0x3fffffff), UINT64_C(1),
       UINT64_C(0x40000000)},
      {__LINE__, u_sub, UINT64_C(1), UINT64_C(1), UINT64_C(0)},
      {__LINE__, u_sub, UINT64_C(1), UINT64_C(0), UINT64_C(1)},
      {__LINE__, u_sub, UINT64_C(-1), UINT64_C(-1), UINT64_C(0)},
      {__LINE__, u_sub, UINT64_C(0x7fffffffffffffff), UINT64_C(-1),
       UINT64_C(0x8000000000000000)},
      {__LINE__, u_sub, UINT64_C(0x8000000000000000), UINT64_C(1),
       UINT64_C(0x7fffffffffffffff)},
      {__LINE__, u_sub, UINT64_C(0x8000000000000000),
       UINT64_C(0x8000000000000000), UINT64_C(0)},
      {__LINE__, u_sub, UINT64_C(0x3fffffff), UINT64_C(-1),
       UINT64_C(0x40000000)},
      {__LINE__, u_mul, UINT64_C(1), UINT64_C(1), UINT64_C(1)},
      {__LINE__, u_mul, UINT64_C(1), UINT64_C(0), UINT64_C(0)},
      {__LINE__, u_mul, UINT64_C(-1), UINT64_C(-1), UINT64_C(1)},
      {__LINE__, u_mul, UINT64_C(0x1000000000000000), UINT64_C(4096),
       UINT64_C(0)},
      {__LINE__, u_mul, UINT64_C(0x8000000000000000), UINT64_C(0), UINT64_C(0)},
      {__LINE__, u_mul, UINT64_C(0x8000000000000000), UINT64_C(-1),
       UINT64_C(0x8000000000000000)},
      {__LINE__, u_mul, UINT64_C(0x7fffffffffffffff), UINT64_C(-1),
       UINT64_C(0x8000000000000001)},
      {__LINE__, u_mul, UINT64_C(0x0123456789abcdef),
       UINT64_C(0xfedcba9876543210), 0x2236d88fe5618cf0},
      {__LINE__, u_mul, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x7fffffffffffffff), UINT64_C(1)},
      {__LINE__, s_div, INT64_C(1), INT64_C(1), INT64_C(1)},
      {__LINE__, s_div, INT64_C(0), INT64_C(1), INT64_C(0)},
      {__LINE__, s_div, INT64_C(0), INT64_C(-1), INT64_C(0)},
      {__LINE__, s_div, INT64_C(-1), INT64_C(-1), INT64_C(1)},
      {__LINE__, s_div, INT64_C(0x8000000000000000), INT64_C(2),
       INT64_C(0xc000000000000000)},
      {__LINE__, s_div, INT64_C(0x8000000000000001), INT64_C(1000),
       INT64_C(0xffdf3b645a1cac09)},
      {__LINE__, s_div, INT64_C(5), INT64_C(2), INT64_C(2)},
      {__LINE__, s_div, INT64_C(-5), INT64_C(2), INT64_C(-2)},
      {__LINE__, s_div, INT64_C(5), INT64_C(-2), INT64_C(-2)},
      {__LINE__, s_div, INT64_C(-5), INT64_C(-2), INT64_C(2)},
      {__LINE__, s_div, INT64_C(7), INT64_C(3), INT64_C(2)},
      {__LINE__, s_div, INT64_C(-7), INT64_C(3), INT64_C(-2)},
      {__LINE__, s_div, INT64_C(7), INT64_C(-3), INT64_C(-2)},
      {__LINE__, s_div, INT64_C(-7), INT64_C(-3), INT64_C(2)},
      {__LINE__, s_div, INT64_C(11), INT64_C(5), INT64_C(2)},
      {__LINE__, s_div, INT64_C(17), INT64_C(7), INT64_C(2)},
      {__LINE__, u_div, UINT64_C(1), UINT64_C(1), UINT64_C(1)},
      {__LINE__, u_div, UINT64_C(0), UINT64_C(1), UINT64_C(0)},
      {__LINE__, u_div, UINT64_C(-1), UINT64_C(-1), UINT64_C(1)},
      {__LINE__, u_div, UINT64_C(0x8000000000000000), UINT64_C(-1),
       UINT64_C(0)},
      {__LINE__, u_div, UINT64_C(0x8000000000000000), UINT64_C(2),
       UINT64_C(0x4000000000000000)},
      {__LINE__, u_div, UINT64_C(0x8ff00ff00ff00ff0), UINT64_C(0x100000001),
       UINT64_C(0x8ff00fef)},
      {__LINE__, u_div, UINT64_C(0x8000000000000001), UINT64_C(1000),
       UINT64_C(0x20c49ba5e353f7)},
      {__LINE__, u_div, UINT64_C(5), UINT64_C(2), UINT64_C(2)},
      {__LINE__, u_div, UINT64_C(-5), UINT64_C(2),
       UINT64_C(0x7ffffffffffffffd)},
      {__LINE__, u_div, UINT64_C(5), UINT64_C(-2), UINT64_C(0)},
      {__LINE__, u_div, UINT64_C(-5), UINT64_C(-2), UINT64_C(0)},
      {__LINE__, u_div, UINT64_C(7), UINT64_C(3), UINT64_C(2)},
      {__LINE__, u_div, UINT64_C(11), UINT64_C(5), UINT64_C(2)},
      {__LINE__, u_div, UINT64_C(17), UINT64_C(7), UINT64_C(2)},
      {__LINE__, s_rem, INT64_C(0x7fffffffffffffff), INT64_C(-1), INT64_C(0)},
      {__LINE__, s_rem, INT64_C(1), INT64_C(1), INT64_C(0)},
      {__LINE__, s_rem, INT64_C(0), INT64_C(1), INT64_C(0)},
      {__LINE__, s_rem, INT64_C(0), INT64_C(-1), INT64_C(0)},
      {__LINE__, s_rem, INT64_C(-1), INT64_C(-1), INT64_C(0)},
      {__LINE__, s_rem, INT64_C(0x8000000000000000), INT64_C(-1), INT64_C(0)},
      {__LINE__, s_rem, INT64_C(0x8000000000000000), INT64_C(2), INT64_C(0)},
      {__LINE__, s_rem, INT64_C(0x8000000000000001), INT64_C(1000),
       INT64_C(-807)},
      {__LINE__, s_rem, INT64_C(5), INT64_C(2), INT64_C(1)},
      {__LINE__, s_rem, INT64_C(-5), INT64_C(2), INT64_C(-1)},
      {__LINE__, s_rem, INT64_C(5), INT64_C(-2), INT64_C(1)},
      {__LINE__, s_rem, INT64_C(-5), INT64_C(-2), INT64_C(-1)},
      {__LINE__, s_rem, INT64_C(7), INT64_C(3), INT64_C(1)},
      {__LINE__, s_rem, INT64_C(-7), INT64_C(3), INT64_C(-1)},
      {__LINE__, s_rem, INT64_C(7), INT64_C(-3), INT64_C(1)},
      {__LINE__, s_rem, INT64_C(-7), INT64_C(-3), INT64_C(-1)},
      {__LINE__, s_rem, INT64_C(11), INT64_C(5), INT64_C(1)},
      {__LINE__, s_rem, INT64_C(17), INT64_C(7), INT64_C(3)},
      {__LINE__, u_rem, UINT64_C(1), UINT64_C(1), UINT64_C(0)},
      {__LINE__, u_rem, UINT64_C(0), UINT64_C(1), UINT64_C(0)},
      {__LINE__, u_rem, UINT64_C(-1), UINT64_C(-1), UINT64_C(0)},
      {__LINE__, u_rem, UINT64_C(0x8000000000000000), UINT64_C(-1),
       UINT64_C(0x8000000000000000)},
      {__LINE__, u_rem, UINT64_C(0x8000000000000000), UINT64_C(2), UINT64_C(0)},
      {__LINE__, u_rem, UINT64_C(0x8ff00ff00ff00ff0), UINT64_C(0x100000001),
       UINT64_C(0x80000001)},
      {__LINE__, u_rem, UINT64_C(0x8000000000000001), UINT64_C(1000),
       UINT64_C(809)},
      {__LINE__, u_rem, UINT64_C(5), UINT64_C(2), UINT64_C(1)},
      {__LINE__, u_rem, UINT64_C(-5), UINT64_C(2), UINT64_C(1)},
      {__LINE__, u_rem, UINT64_C(5), UINT64_C(-2), UINT64_C(5)},
      {__LINE__, u_rem, UINT64_C(-5), UINT64_C(-2), UINT64_C(-5)},
      {__LINE__, u_rem, UINT64_C(7), UINT64_C(3), UINT64_C(1)},
      {__LINE__, u_rem, UINT64_C(11), UINT64_C(5), UINT64_C(1)},
      {__LINE__, u_rem, UINT64_C(17), UINT64_C(7), UINT64_C(3)},
      {__LINE__, u_and, UINT64_C(1), UINT64_C(0), UINT64_C(0)},
      {__LINE__, u_and, UINT64_C(0), UINT64_C(1), UINT64_C(0)},
      {__LINE__, u_and, UINT64_C(1), UINT64_C(1), UINT64_C(1)},
      {__LINE__, u_and, UINT64_C(0), UINT64_C(0), UINT64_C(0)},
      {__LINE__, u_and, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x8000000000000000), UINT64_C(0)},
      {__LINE__, u_and, UINT64_C(0x7fffffffffffffff), UINT64_C(-1),
       UINT64_C(0x7fffffffffffffff)},
      {__LINE__, u_and, UINT64_C(0xf0f0ffff), UINT64_C(0xfffff0f0),
       UINT64_C(0xf0f0f0f0)},
      {__LINE__, u_and, UINT64_C(0xffffffffffffffff),
       UINT64_C(0xffffffffffffffff), 0xffffffffffffffff},
      {__LINE__, u_or, UINT64_C(1), UINT64_C(0), UINT64_C(1)},
      {__LINE__, u_or, UINT64_C(0), UINT64_C(1), UINT64_C(1)},
      {__LINE__, u_or, UINT64_C(1), UINT64_C(1), UINT64_C(1)},
      {__LINE__, u_or, UINT64_C(0), UINT64_C(0), UINT64_C(0)},
      {__LINE__, u_or, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x8000000000000000), UINT64_C(-1)},
      {__LINE__, u_or, UINT64_C(0x8000000000000000), UINT64_C(0),
       UINT64_C(0x8000000000000000)},
      {__LINE__, u_or, UINT64_C(0xf0f0ffff), UINT64_C(0xfffff0f0),
       UINT64_C(0xffffffff)},
      {__LINE__, u_or, UINT64_C(0xffffffffffffffff),
       UINT64_C(0xffffffffffffffff), 0xffffffffffffffff},
      {__LINE__, u_xor, UINT64_C(1), UINT64_C(0), UINT64_C(1)},
      {__LINE__, u_xor, UINT64_C(0), UINT64_C(1), UINT64_C(1)},
      {__LINE__, u_xor, UINT64_C(1), UINT64_C(1), UINT64_C(0)},
      {__LINE__, u_xor, UINT64_C(0), UINT64_C(0), UINT64_C(0)},
      {__LINE__, u_xor, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x8000000000000000), UINT64_C(-1)},
      {__LINE__, u_xor, UINT64_C(0x8000000000000000), UINT64_C(0),
       UINT64_C(0x8000000000000000)},
      {__LINE__, u_xor, UINT64_C(-1), UINT64_C(0x8000000000000000),
       UINT64_C(0x7fffffffffffffff)},
      {__LINE__, u_xor, UINT64_C(-1), UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x8000000000000000)},
      {__LINE__, u_xor, UINT64_C(0xf0f0ffff), UINT64_C(0xfffff0f0),
       UINT64_C(0x0f0f0f0f)},
      {__LINE__, u_xor, UINT64_C(0xffffffffffffffff),
       UINT64_C(0xffffffffffffffff), UINT64_C(0)},
      {__LINE__, u_shl, UINT64_C(1), UINT64_C(1), UINT64_C(2)},
      {__LINE__, u_shl, UINT64_C(1), UINT64_C(0), UINT64_C(1)},
      {__LINE__, u_shl, UINT64_C(0x7fffffffffffffff), UINT64_C(1),
       UINT64_C(0xfffffffffffffffe)},
      {__LINE__, u_shl, UINT64_C(0xffffffffffffffff), UINT64_C(1),
       UINT64_C(0xfffffffffffffffe)},
      {__LINE__, u_shl, UINT64_C(0x8000000000000000), UINT64_C(1), UINT64_C(0)},
      {__LINE__, u_shl, UINT64_C(0x4000000000000000), UINT64_C(1),
       UINT64_C(0x8000000000000000)},
      {__LINE__, u_shl, UINT64_C(1), UINT64_C(63),
       UINT64_C(0x8000000000000000)},
      {__LINE__, u_shl, UINT64_C(1), UINT64_C(64), UINT64_C(1)},
      {__LINE__, u_shl, UINT64_C(1), UINT64_C(65), UINT64_C(2)},
      {__LINE__, u_shl, UINT64_C(1), UINT64_C(-1),
       UINT64_C(0x8000000000000000)},
      {__LINE__, u_shl, UINT64_C(1), UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x8000000000000000)},
      {__LINE__, s_shr, INT64_C(1), INT64_C(1), INT64_C(0)},
      {__LINE__, s_shr, INT64_C(1), INT64_C(0), INT64_C(1)},
      {__LINE__, s_shr, INT64_C(-1), INT64_C(1), INT64_C(-1)},
      {__LINE__, s_shr, INT64_C(0x7fffffffffffffff), INT64_C(1),
       INT64_C(0x3fffffffffffffff)},
      {__LINE__, s_shr, INT64_C(0x8000000000000000), INT64_C(1),
       INT64_C(0xc000000000000000)},
      {__LINE__, s_shr, INT64_C(0x4000000000000000), INT64_C(1),
       INT64_C(0x2000000000000000)},
      {__LINE__, s_shr, INT64_C(1), INT64_C(64), INT64_C(1)},
      {__LINE__, s_shr, INT64_C(1), INT64_C(65), INT64_C(0)},
      {__LINE__, s_shr, INT64_C(1), INT64_C(-1), INT64_C(0)},
      {__LINE__, s_shr, INT64_C(1), INT64_C(0x7fffffffffffffff), INT64_C(0)},
      {__LINE__, s_shr, INT64_C(1), INT64_C(0x8000000000000000), INT64_C(1)},
      {__LINE__, s_shr, INT64_C(0x8000000000000000), INT64_C(63), INT64_C(-1)},
      {__LINE__, s_shr, INT64_C(-1), INT64_C(64), INT64_C(-1)},
      {__LINE__, s_shr, INT64_C(-1), INT64_C(65), INT64_C(-1)},
      {__LINE__, s_shr, INT64_C(-1), INT64_C(-1), INT64_C(-1)},
      {__LINE__, s_shr, INT64_C(-1), INT64_C(0x7fffffffffffffff), INT64_C(-1)},
      {__LINE__, s_shr, INT64_C(-1), INT64_C(0x8000000000000000), INT64_C(-1)},
      {__LINE__, u_shr, UINT64_C(1), UINT64_C(1), UINT64_C(0)},
      {__LINE__, u_shr, UINT64_C(1), UINT64_C(0), UINT64_C(1)},
      {__LINE__, u_shr, UINT64_C(-1), UINT64_C(1),
       UINT64_C(0x7fffffffffffffff)},
      {__LINE__, u_shr, UINT64_C(0x7fffffffffffffff), UINT64_C(1),
       UINT64_C(0x3fffffffffffffff)},
      {__LINE__, u_shr, UINT64_C(0x8000000000000000), UINT64_C(1),
       UINT64_C(0x4000000000000000)},
      {__LINE__, u_shr, UINT64_C(0x4000000000000000), UINT64_C(1),
       UINT64_C(0x2000000000000000)},
      {__LINE__, u_shr, UINT64_C(1), UINT64_C(64), UINT64_C(1)},
      {__LINE__, u_shr, UINT64_C(1), UINT64_C(65), UINT64_C(0)},
      {__LINE__, u_shr, UINT64_C(1), UINT64_C(-1), UINT64_C(0)},
      {__LINE__, u_shr, UINT64_C(1), UINT64_C(0x7fffffffffffffff), UINT64_C(0)},
      {__LINE__, u_shr, UINT64_C(1), UINT64_C(0x8000000000000000), UINT64_C(1)},
      {__LINE__, u_shr, UINT64_C(0x8000000000000000), UINT64_C(63),
       UINT64_C(1)},
      {__LINE__, u_shr, UINT64_C(-1), UINT64_C(64), UINT64_C(-1)},
      {__LINE__, u_shr, UINT64_C(-1), UINT64_C(65),
       UINT64_C(0x7fffffffffffffff)},
      {__LINE__, u_shr, UINT64_C(-1), UINT64_C(-1), UINT64_C(1)},
      {__LINE__, u_shr, UINT64_C(-1), UINT64_C(0x7fffffffffffffff),
       UINT64_C(1)},
      {__LINE__, u_shr, UINT64_C(-1), UINT64_C(0x8000000000000000),
       UINT64_C(-1)},
      {__LINE__, u_rotl, UINT64_C(1), UINT64_C(1), UINT64_C(2)},
      {__LINE__, u_rotl, UINT64_C(1), UINT64_C(0), UINT64_C(1)},
      {__LINE__, u_rotl, UINT64_C(-1), UINT64_C(1), UINT64_C(-1)},
      {__LINE__, u_rotl, UINT64_C(1), UINT64_C(64), UINT64_C(1)},
      {__LINE__, u_rotl, UINT64_C(0xabcd987602468ace), UINT64_C(1),
       UINT64_C(0x579b30ec048d159d)},
      {__LINE__, u_rotl, UINT64_C(0xfe000000dc000000), UINT64_C(4),
       UINT64_C(0xe000000dc000000f)},
      {__LINE__, u_rotl, UINT64_C(0xabcd1234ef567809), UINT64_C(53),
       UINT64_C(0x013579a2469deacf)},
      {__LINE__, u_rotl, UINT64_C(0xabd1234ef567809c), UINT64_C(63),
       UINT64_C(0x55e891a77ab3c04e)},
      {__LINE__, u_rotl, UINT64_C(0xabcd1234ef567809), UINT64_C(0xf5),
       UINT64_C(0x013579a2469deacf)},
      {__LINE__, u_rotl, UINT64_C(0xabcd7294ef567809),
       UINT64_C(0xffffffffffffffed), 0xcf013579ae529dea},
      {__LINE__, u_rotl, UINT64_C(0xabd1234ef567809c),
       UINT64_C(0x800000000000003f), 0x55e891a77ab3c04e},
      {__LINE__, u_rotl, UINT64_C(1), UINT64_C(63),
       UINT64_C(0x8000000000000000)},
      {__LINE__, u_rotl, UINT64_C(0x8000000000000000), UINT64_C(1),
       UINT64_C(1)},
      {__LINE__, u_rotr, UINT64_C(1), UINT64_C(1),
       UINT64_C(0x8000000000000000)},
      {__LINE__, u_rotr, UINT64_C(1), UINT64_C(0), UINT64_C(1)},
      {__LINE__, u_rotr, UINT64_C(-1), UINT64_C(1), UINT64_C(-1)},
      {__LINE__, u_rotr, UINT64_C(1), UINT64_C(64), UINT64_C(1)},
      {__LINE__, u_rotr, UINT64_C(0xabcd987602468ace), UINT64_C(1),
       UINT64_C(0x55e6cc3b01234567)},
      {__LINE__, u_rotr, UINT64_C(0xfe000000dc000000), UINT64_C(4),
       UINT64_C(0x0fe000000dc00000)},
      {__LINE__, u_rotr, UINT64_C(0xabcd1234ef567809), UINT64_C(53),
       UINT64_C(0x6891a77ab3c04d5e)},
      {__LINE__, u_rotr, UINT64_C(0xabd1234ef567809c), UINT64_C(63),
       UINT64_C(0x57a2469deacf0139)},
      {__LINE__, u_rotr, UINT64_C(0xabcd1234ef567809), UINT64_C(0xf5),
       UINT64_C(0x6891a77ab3c04d5e)},
      {__LINE__, u_rotr, UINT64_C(0xabcd7294ef567809),
       UINT64_C(0xffffffffffffffed), 0x94a77ab3c04d5e6b},
      {__LINE__, u_rotr, UINT64_C(0xabd1234ef567809c),
       UINT64_C(0x800000000000003f), 0x57a2469deacf0139},
      {__LINE__, u_rotr, UINT64_C(1), UINT64_C(63), UINT64_C(2)},
      {__LINE__, u_rotr, UINT64_C(0x8000000000000000), UINT64_C(63),
       UINT64_C(1)},
  };
  static const struct data4 d4[] = {
      {__LINE__, u_eq, UINT64_C(0), UINT64_C(0), true},
      {__LINE__, u_eq, UINT64_C(1), UINT64_C(1), true},
      {__LINE__, u_eq, UINT64_C(-1), UINT64_C(1), false},
      {__LINE__, u_eq, UINT64_C(0x8000000000000000),
       UINT64_C(0x8000000000000000), true},
      {__LINE__, u_eq, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x7fffffffffffffff), true},
      {__LINE__, u_eq, UINT64_C(-1), UINT64_C(-1), true},
      {__LINE__, u_eq, UINT64_C(1), UINT64_C(0), false},
      {__LINE__, u_eq, UINT64_C(0), UINT64_C(1), false},
      {__LINE__, u_eq, UINT64_C(0x8000000000000000), UINT64_C(0), false},
      {__LINE__, u_eq, UINT64_C(0), UINT64_C(0x8000000000000000), false},
      {__LINE__, u_eq, UINT64_C(0x8000000000000000), UINT64_C(-1), false},
      {__LINE__, u_eq, UINT64_C(-1), UINT64_C(0x8000000000000000), false},
      {__LINE__, u_eq, UINT64_C(0x8000000000000000),
       UINT64_C(0x7fffffffffffffff), false},
      {__LINE__, u_eq, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x8000000000000000), false},
      {__LINE__, u_ne, UINT64_C(0), UINT64_C(0), false},
      {__LINE__, u_ne, UINT64_C(1), UINT64_C(1), false},
      {__LINE__, u_ne, UINT64_C(-1), UINT64_C(1), true},
      {__LINE__, u_ne, UINT64_C(0x8000000000000000),
       UINT64_C(0x8000000000000000), false},
      {__LINE__, u_ne, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x7fffffffffffffff), false},
      {__LINE__, u_ne, UINT64_C(-1), UINT64_C(-1), false},
      {__LINE__, u_ne, UINT64_C(1), UINT64_C(0), true},
      {__LINE__, u_ne, UINT64_C(0), UINT64_C(1), true},
      {__LINE__, u_ne, UINT64_C(0x8000000000000000), UINT64_C(0), true},
      {__LINE__, u_ne, UINT64_C(0), UINT64_C(0x8000000000000000), true},
      {__LINE__, u_ne, UINT64_C(0x8000000000000000), UINT64_C(-1), true},
      {__LINE__, u_ne, UINT64_C(-1), UINT64_C(0x8000000000000000), true},
      {__LINE__, u_ne, UINT64_C(0x8000000000000000),
       UINT64_C(0x7fffffffffffffff), true},
      {__LINE__, u_ne, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x8000000000000000), true},
      {__LINE__, s_lt, INT64_C(0), INT64_C(0), false},
      {__LINE__, s_lt, INT64_C(1), INT64_C(1), false},
      {__LINE__, s_lt, INT64_C(-1), INT64_C(1), true},
      {__LINE__, s_lt, INT64_C(0x8000000000000000), INT64_C(0x8000000000000000),
       false},
      {__LINE__, s_lt, INT64_C(0x7fffffffffffffff), INT64_C(0x7fffffffffffffff),
       false},
      {__LINE__, s_lt, INT64_C(-1), INT64_C(-1), false},
      {__LINE__, s_lt, INT64_C(1), INT64_C(0), false},
      {__LINE__, s_lt, INT64_C(0), INT64_C(1), true},
      {__LINE__, s_lt, INT64_C(0x8000000000000000), INT64_C(0), true},
      {__LINE__, s_lt, INT64_C(0), INT64_C(0x8000000000000000), false},
      {__LINE__, s_lt, INT64_C(0x8000000000000000), INT64_C(-1), true},
      {__LINE__, s_lt, INT64_C(-1), INT64_C(0x8000000000000000), false},
      {__LINE__, s_lt, INT64_C(0x8000000000000000), INT64_C(0x7fffffffffffffff),
       true},
      {__LINE__, s_lt, INT64_C(0x7fffffffffffffff), INT64_C(0x8000000000000000),
       false},
      {__LINE__, u_lt, UINT64_C(0), UINT64_C(0), false},
      {__LINE__, u_lt, UINT64_C(1), UINT64_C(1), false},
      {__LINE__, u_lt, UINT64_C(-1), UINT64_C(1), false},
      {__LINE__, u_lt, UINT64_C(0x8000000000000000),
       UINT64_C(0x8000000000000000), false},
      {__LINE__, u_lt, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x7fffffffffffffff), false},
      {__LINE__, u_lt, UINT64_C(-1), UINT64_C(-1), false},
      {__LINE__, u_lt, UINT64_C(1), UINT64_C(0), false},
      {__LINE__, u_lt, UINT64_C(0), UINT64_C(1), true},
      {__LINE__, u_lt, UINT64_C(0x8000000000000000), UINT64_C(0), false},
      {__LINE__, u_lt, UINT64_C(0), UINT64_C(0x8000000000000000), true},
      {__LINE__, u_lt, UINT64_C(0x8000000000000000), UINT64_C(-1), true},
      {__LINE__, u_lt, UINT64_C(-1), UINT64_C(0x8000000000000000), false},
      {__LINE__, u_lt, UINT64_C(0x8000000000000000),
       UINT64_C(0x7fffffffffffffff), false},
      {__LINE__, u_lt, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x8000000000000000), true},
      {__LINE__, s_le, INT64_C(0), INT64_C(0), true},
      {__LINE__, s_le, INT64_C(1), INT64_C(1), true},
      {__LINE__, s_le, INT64_C(-1), INT64_C(1), true},
      {__LINE__, s_le, INT64_C(0x8000000000000000), INT64_C(0x8000000000000000),
       true},
      {__LINE__, s_le, INT64_C(0x7fffffffffffffff), INT64_C(0x7fffffffffffffff),
       true},
      {__LINE__, s_le, INT64_C(-1), INT64_C(-1), true},
      {__LINE__, s_le, INT64_C(1), INT64_C(0), false},
      {__LINE__, s_le, INT64_C(0), INT64_C(1), true},
      {__LINE__, s_le, INT64_C(0x8000000000000000), INT64_C(0), true},
      {__LINE__, s_le, INT64_C(0), INT64_C(0x8000000000000000), false},
      {__LINE__, s_le, INT64_C(0x8000000000000000), INT64_C(-1), true},
      {__LINE__, s_le, INT64_C(-1), INT64_C(0x8000000000000000), false},
      {__LINE__, s_le, INT64_C(0x8000000000000000), INT64_C(0x7fffffffffffffff),
       true},
      {__LINE__, s_le, INT64_C(0x7fffffffffffffff), INT64_C(0x8000000000000000),
       false},
      {__LINE__, u_le, UINT64_C(0), UINT64_C(0), true},
      {__LINE__, u_le, UINT64_C(1), UINT64_C(1), true},
      {__LINE__, u_le, UINT64_C(-1), UINT64_C(1), false},
      {__LINE__, u_le, UINT64_C(0x8000000000000000),
       UINT64_C(0x8000000000000000), true},
      {__LINE__, u_le, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x7fffffffffffffff), true},
      {__LINE__, u_le, UINT64_C(-1), UINT64_C(-1), true},
      {__LINE__, u_le, UINT64_C(1), UINT64_C(0), false},
      {__LINE__, u_le, UINT64_C(0), UINT64_C(1), true},
      {__LINE__, u_le, UINT64_C(0x8000000000000000), UINT64_C(0), false},
      {__LINE__, u_le, UINT64_C(0), UINT64_C(0x8000000000000000), true},
      {__LINE__, u_le, UINT64_C(0x8000000000000000), UINT64_C(-1), true},
      {__LINE__, u_le, UINT64_C(-1), UINT64_C(0x8000000000000000), false},
      {__LINE__, u_le, UINT64_C(0x8000000000000000),
       UINT64_C(0x7fffffffffffffff), false},
      {__LINE__, u_le, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x8000000000000000), true},
      {__LINE__, s_gt, INT64_C(0), INT64_C(0), false},
      {__LINE__, s_gt, INT64_C(1), INT64_C(1), false},
      {__LINE__, s_gt, INT64_C(-1), INT64_C(1), false},
      {__LINE__, s_gt, INT64_C(0x8000000000000000), INT64_C(0x8000000000000000),
       false},
      {__LINE__, s_gt, INT64_C(0x7fffffffffffffff), INT64_C(0x7fffffffffffffff),
       false},
      {__LINE__, s_gt, INT64_C(-1), INT64_C(-1), false},
      {__LINE__, s_gt, INT64_C(1), INT64_C(0), true},
      {__LINE__, s_gt, INT64_C(0), INT64_C(1), false},
      {__LINE__, s_gt, INT64_C(0x8000000000000000), INT64_C(0), false},
      {__LINE__, s_gt, INT64_C(0), INT64_C(0x8000000000000000), true},
      {__LINE__, s_gt, INT64_C(0x8000000000000000), INT64_C(-1), false},
      {__LINE__, s_gt, INT64_C(-1), INT64_C(0x8000000000000000), true},
      {__LINE__, s_gt, INT64_C(0x8000000000000000), INT64_C(0x7fffffffffffffff),
       false},
      {__LINE__, s_gt, INT64_C(0x7fffffffffffffff),
       UINT64_C(0x8000000000000000), true},
      {__LINE__, u_gt, UINT64_C(0), UINT64_C(0), false},
      {__LINE__, u_gt, UINT64_C(1), UINT64_C(1), false},
      {__LINE__, u_gt, UINT64_C(-1), UINT64_C(1), true},
      {__LINE__, u_gt, UINT64_C(0x8000000000000000),
       UINT64_C(0x8000000000000000), false},
      {__LINE__, u_gt, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x7fffffffffffffff), false},
      {__LINE__, u_gt, UINT64_C(-1), UINT64_C(-1), false},
      {__LINE__, u_gt, UINT64_C(1), UINT64_C(0), true},
      {__LINE__, u_gt, UINT64_C(0), UINT64_C(1), false},
      {__LINE__, u_gt, UINT64_C(0x8000000000000000), UINT64_C(0), true},
      {__LINE__, u_gt, UINT64_C(0), UINT64_C(0x8000000000000000), false},
      {__LINE__, u_gt, UINT64_C(0x8000000000000000), UINT64_C(-1), false},
      {__LINE__, u_gt, UINT64_C(-1), UINT64_C(0x8000000000000000), true},
      {__LINE__, u_gt, UINT64_C(0x8000000000000000),
       UINT64_C(0x7fffffffffffffff), true},
      {__LINE__, u_gt, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x8000000000000000), false},
      {__LINE__, s_ge, INT64_C(0), INT64_C(0), true},
      {__LINE__, s_ge, INT64_C(1), INT64_C(1), true},
      {__LINE__, s_ge, INT64_C(-1), INT64_C(1), false},
      {__LINE__, s_ge, INT64_C(0x8000000000000000), INT64_C(0x8000000000000000),
       true},
      {__LINE__, s_ge, INT64_C(0x7fffffffffffffff), INT64_C(0x7fffffffffffffff),
       true},
      {__LINE__, s_ge, INT64_C(-1), INT64_C(-1), true},
      {__LINE__, s_ge, INT64_C(1), INT64_C(0), true},
      {__LINE__, s_ge, INT64_C(0), INT64_C(1), false},
      {__LINE__, s_ge, INT64_C(0x8000000000000000), INT64_C(0), false},
      {__LINE__, s_ge, INT64_C(0), INT64_C(0x8000000000000000), true},
      {__LINE__, s_ge, INT64_C(0x8000000000000000), INT64_C(-1), false},
      {__LINE__, s_ge, INT64_C(-1), INT64_C(0x8000000000000000), true},
      {__LINE__, s_ge, INT64_C(0x8000000000000000), INT64_C(0x7fffffffffffffff),
       false},
      {__LINE__, s_ge, INT64_C(0x7fffffffffffffff), INT64_C(0x8000000000000000),
       true},
      {__LINE__, u_ge, UINT64_C(0), UINT64_C(0), true},
      {__LINE__, u_ge, UINT64_C(1), UINT64_C(1), true},
      {__LINE__, u_ge, UINT64_C(-1), UINT64_C(1), true},
      {__LINE__, u_ge, UINT64_C(0x8000000000000000),
       UINT64_C(0x8000000000000000), true},
      {__LINE__, u_ge, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x7fffffffffffffff), true},
      {__LINE__, u_ge, UINT64_C(-1), UINT64_C(-1), true},
      {__LINE__, u_ge, UINT64_C(1), UINT64_C(0), true},
      {__LINE__, u_ge, UINT64_C(0), UINT64_C(1), false},
      {__LINE__, u_ge, UINT64_C(0x8000000000000000), UINT64_C(0), true},
      {__LINE__, u_ge, UINT64_C(0), UINT64_C(0x8000000000000000), false},
      {__LINE__, u_ge, UINT64_C(0x8000000000000000), UINT64_C(-1), false},
      {__LINE__, u_ge, UINT64_C(-1), UINT64_C(0x8000000000000000), true},
      {__LINE__, u_ge, UINT64_C(0x8000000000000000),
       UINT64_C(0x7fffffffffffffff), true},
      {__LINE__, u_ge, UINT64_C(0x7fffffffffffffff),
       UINT64_C(0x8000000000000000), false},
  };

  for (size_t i = 0; i < sizeof(d1) / sizeof(d1[0]); ++i) {
    check1(d1[i].line, d1[i].func, d1[i].v, d1[i].r);
  }
  for (size_t i = 0; i < sizeof(d2) / sizeof(d2[0]); ++i) {
    check2(d2[i].line, d2[i].func, d2[i].v, d2[i].r);
  }
  for (size_t i = 0; i < sizeof(d3) / sizeof(d3[0]); ++i) {
    check3(d3[i].line, d3[i].func, d3[i].v1, d3[i].v2, d3[i].r);
  }
  for (size_t i = 0; i < sizeof(d4) / sizeof(d4[0]); ++i) {
    check4(d4[i].line, d4[i].func, d4[i].v1, d4[i].v2, d4[i].r);
  }

  return 0;
}
