#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOINLINE __attribute__((noinline))

NOINLINE uint32_t u_add(uint32_t a, uint32_t b) { return a + b; }
NOINLINE uint32_t u_sub(uint32_t a, uint32_t b) { return a - b; }
NOINLINE uint32_t u_mul(uint32_t a, uint32_t b) { return a * b; }
NOINLINE uint32_t u_div(uint32_t a, uint32_t b) { return a / b; }
NOINLINE uint32_t s_div(uint32_t a, uint32_t b) {
  return ((int32_t)a) / ((int32_t)b);
}
NOINLINE uint32_t u_rem(uint32_t a, uint32_t b) { return a % b; }
NOINLINE uint32_t s_rem(uint32_t a, uint32_t b) {
  int32_t x = a;
  int32_t y = b;
#ifndef __wasm32__
  if (x == INT32_MIN && y == -1) {
    return 0;
  }
#endif
  return x % y;
}
NOINLINE uint32_t u_and(uint32_t a, uint32_t b) { return a & b; }
NOINLINE uint32_t u_or(uint32_t a, uint32_t b) { return a | b; }
NOINLINE uint32_t u_xor(uint32_t a, uint32_t b) { return a ^ b; }
NOINLINE uint32_t u_shl(uint32_t a, uint32_t b) { return a << b; }
NOINLINE uint32_t u_shr(uint32_t a, uint32_t b) { return a >> b; }
NOINLINE uint32_t s_shr(uint32_t a, uint32_t b) {
  return ((int32_t)a) >> ((int32_t)b);
}
NOINLINE uint32_t u_rotl(uint32_t a, uint32_t b) {
  return (a << b) | (a >> (sizeof(a) * 8 - b));
}
NOINLINE uint32_t u_rotr(uint32_t a, uint32_t b) {
  return (a >> b) | (a << (sizeof(a) * 8 - b));
}
NOINLINE uint32_t u_clz(uint32_t a) {
  return a == 0 ? sizeof(a) * 8 : __builtin_clz(a);
}
NOINLINE uint32_t u_ctz(uint32_t a) {
  return a == 0 ? sizeof(a) * 8 : __builtin_ctz(a);
}
NOINLINE uint32_t u_popcnt(uint32_t a) { return __builtin_popcount(a); }
NOINLINE uint32_t s_extend8(uint32_t a) { return (int32_t)(int8_t)(int32_t)a; }
NOINLINE uint32_t s_extend16(uint32_t a) {
  return (int32_t)(int16_t)(int32_t)a;
}
NOINLINE bool u_eqz(uint32_t a) { return a == UINT32_C(0); }
NOINLINE bool u_eq(uint32_t a, uint32_t b) { return a == b; }
NOINLINE bool u_ne(uint32_t a, uint32_t b) { return a != b; }
NOINLINE bool u_lt(uint32_t a, uint32_t b) { return a < b; }
NOINLINE bool s_lt(uint32_t a, uint32_t b) {
  return ((int32_t)a) < ((int32_t)b);
}
NOINLINE bool u_le(uint32_t a, uint32_t b) { return a <= b; }
NOINLINE bool s_le(uint32_t a, uint32_t b) {
  return ((int32_t)a) <= ((int32_t)b);
}
NOINLINE bool u_gt(uint32_t a, uint32_t b) { return a > b; }
NOINLINE bool s_gt(uint32_t a, uint32_t b) {
  return ((int32_t)a) > ((int32_t)b);
}
NOINLINE bool u_ge(uint32_t a, uint32_t b) { return a >= b; }
NOINLINE bool s_ge(uint32_t a, uint32_t b) {
  return ((int32_t)a) >= ((int32_t)b);
}

NOINLINE bool eq(uint32_t a, uint32_t b) { return a == b; }

static inline void check1(uint32_t line, uint32_t (*func)(uint32_t), uint32_t a,
                          uint32_t b) {
  const uint32_t x = func(a);
  if (!eq(x, b)) {
    printf("%" PRIu32 " 0x%08" PRIx32 " 0x%08" PRIx32 " 0x%08" PRIx32 "\n",
           line, a, x, b);
  }
}

static inline void check2(uint32_t line, bool (*func)(uint32_t), uint32_t a,
                          bool b) {
  const bool x = func(a);
  if (!eq(x, b)) {
    printf("%" PRIu32 " 0x%08" PRIx32 " 0x%08d 0x%08d\n", line, a, x, b);
  }
}

static inline void check3(uint32_t line, uint32_t (*func)(uint32_t, uint32_t),
                          uint32_t a, uint32_t b, uint32_t c) {
  const uint32_t x = func(a, b);
  if (!eq(x, c)) {
    printf("%" PRIu32 " 0x%08" PRIx32 " 0x%08" PRIx32 " 0x%08" PRIx32
           " 0x%08" PRIx32 "\n",
           line, a, b, x, c);
  }
}

static inline void check4(uint32_t line, bool (*func)(uint32_t, uint32_t),
                          uint32_t a, uint32_t b, bool c) {
  const bool x = func(a, b);
  if (x != c) {
    printf("%" PRIu32 " 0x%08" PRIx32 " 0x%08" PRIx32 " %d %d\n", line, a, b, x,
           c);
  }
}

struct data1 {
  uint32_t line;
  uint32_t (*func)(uint32_t);
  uint32_t v;
  uint32_t r;
};
struct data2 {
  uint32_t line;
  bool (*func)(uint32_t);
  uint32_t v;
  bool r;
};
struct data3 {
  uint32_t line;
  uint32_t (*func)(uint32_t, uint32_t);
  uint32_t v1;
  uint32_t v2;
  uint32_t r;
};
struct data4 {
  uint32_t line;
  bool (*func)(uint32_t, uint32_t);
  uint32_t v1;
  uint32_t v2;
  bool r;
};
int main(int argc, char **argv) {
  static const struct data1 d1[] = {
      {__LINE__, u_clz, 0xffffffff, 0},
      {__LINE__, u_clz, 0, 32},
      {__LINE__, u_clz, 0x00008000, 16},
      {__LINE__, u_clz, 0xff, 24},
      {__LINE__, u_clz, 0x80000000, 0},
      {__LINE__, u_clz, 1, 31},
      {__LINE__, u_clz, 2, 30},
      {__LINE__, u_clz, 0x7fffffff, 1},
      {__LINE__, u_ctz, -1, 0},
      {__LINE__, u_ctz, 0, 32},
      {__LINE__, u_ctz, 0x00008000, 15},
      {__LINE__, u_ctz, 0x00010000, 16},
      {__LINE__, u_ctz, 0x80000000, 31},
      {__LINE__, u_ctz, 0x7fffffff, 0},
      {__LINE__, u_popcnt, -1, 32},
      {__LINE__, u_popcnt, 0, 0},
      {__LINE__, u_popcnt, 0x00008000, 1},
      {__LINE__, u_popcnt, 0x80008000, 2},
      {__LINE__, u_popcnt, 0x7fffffff, 31},
      {__LINE__, u_popcnt, 0xAAAAAAAA, 16},
      {__LINE__, u_popcnt, 0x55555555, 16},
      {__LINE__, u_popcnt, 0xDEADBEEF, 24},
      {__LINE__, s_extend8, 0, 0},
      {__LINE__, s_extend8, 0x7f, 127},
      {__LINE__, s_extend8, 0x80, -128},
      {__LINE__, s_extend8, 0xff, -1},
      {__LINE__, s_extend8, 0x01234500, 0},
      {__LINE__, s_extend8, 0xfedcba80, -0x80},
      {__LINE__, s_extend8, -1, -1},
      {__LINE__, s_extend16, 0, 0},
      {__LINE__, s_extend16, 0x7fff, 32767},
      {__LINE__, s_extend16, 0x8000, -32768},
      {__LINE__, s_extend16, 0xffff, -1},
      {__LINE__, s_extend16, 0x01230000, 0},
      {__LINE__, s_extend16, 0xfedc8000, -0x8000},
      {__LINE__, s_extend16, -1, -1},
  };
  static const struct data2 d2[] = {
      {__LINE__, u_eqz, 0, 1},          {__LINE__, u_eqz, 1, 0},
      {__LINE__, u_eqz, 0x80000000, 0}, {__LINE__, u_eqz, 0x7fffffff, 0},
      {__LINE__, u_eqz, 0xffffffff, 0},
  };
  static const struct data3 d3[] = {
      {__LINE__, u_add, 1, 1, 2},
      {__LINE__, u_add, 1, 0, 1},
      {__LINE__, u_add, -1, -1, -2},
      {__LINE__, u_add, -1, 1, 0},
      {__LINE__, u_add, 0x7fffffff, 1, 0x80000000},
      {__LINE__, u_add, 0x80000000, -1, 0x7fffffff},
      {__LINE__, u_add, 0x80000000, 0x80000000, 0},
      {__LINE__, u_add, 0x3fffffff, 1, 0x40000000},
      {__LINE__, u_sub, 1, 1, 0},
      {__LINE__, u_sub, 1, 0, 1},
      {__LINE__, u_sub, -1, -1, 0},
      {__LINE__, u_sub, 0x7fffffff, -1, 0x80000000},
      {__LINE__, u_sub, 0x80000000, 1, 0x7fffffff},
      {__LINE__, u_sub, 0x80000000, 0x80000000, 0},
      {__LINE__, u_sub, 0x3fffffff, -1, 0x40000000},
      {__LINE__, u_mul, 1, 1, 1},
      {__LINE__, u_mul, 1, 0, 0},
      {__LINE__, u_mul, -1, -1, 1},
      {__LINE__, u_mul, 0x10000000, 4096, 0},
      {__LINE__, u_mul, 0x80000000, 0, 0},
      {__LINE__, u_mul, 0x80000000, -1, 0x80000000},
      {__LINE__, u_mul, 0x7fffffff, -1, 0x80000001},
      {__LINE__, u_mul, 0x01234567, 0x76543210, 0x358e7470},
      {__LINE__, u_mul, 0x7fffffff, 0x7fffffff, 1},
      {__LINE__, s_div, 1, 1, 1},
      {__LINE__, s_div, 0, 1, 0},
      {__LINE__, s_div, 0, -1, 0},
      {__LINE__, s_div, -1, -1, 1},
      {__LINE__, s_div, 0x80000000, 2, 0xc0000000},
      {__LINE__, s_div, 0x80000001, 1000, 0xffdf3b65},
      {__LINE__, s_div, 5, 2, 2},
      {__LINE__, s_div, -5, 2, -2},
      {__LINE__, s_div, 5, -2, -2},
      {__LINE__, s_div, -5, -2, 2},
      {__LINE__, s_div, 7, 3, 2},
      {__LINE__, s_div, -7, 3, -2},
      {__LINE__, s_div, 7, -3, -2},
      {__LINE__, s_div, -7, -3, 2},
      {__LINE__, s_div, 11, 5, 2},
      {__LINE__, s_div, 17, 7, 2},
      {__LINE__, u_div, 1, 1, 1},
      {__LINE__, u_div, 0, 1, 0},
      {__LINE__, u_div, -1, -1, 1},
      {__LINE__, u_div, 0x80000000, -1, 0},
      {__LINE__, u_div, 0x80000000, 2, 0x40000000},
      {__LINE__, u_div, 0x8ff00ff0, 0x10001, 0x8fef},
      {__LINE__, u_div, 0x80000001, 1000, 0x20c49b},
      {__LINE__, u_div, 5, 2, 2},
      {__LINE__, u_div, -5, 2, 0x7ffffffd},
      {__LINE__, u_div, 5, -2, 0},
      {__LINE__, u_div, -5, -2, 0},
      {__LINE__, u_div, 7, 3, 2},
      {__LINE__, u_div, 11, 5, 2},
      {__LINE__, u_div, 17, 7, 2},
      {__LINE__, s_rem, 0x7fffffff, -1, 0},
      {__LINE__, s_rem, 1, 1, 0},
      {__LINE__, s_rem, 0, 1, 0},
      {__LINE__, s_rem, 0, -1, 0},
      {__LINE__, s_rem, -1, -1, 0},
      {__LINE__, s_rem, 0x80000000, -1, 0},
      {__LINE__, s_rem, 0x80000000, 2, 0},
      {__LINE__, s_rem, 0x80000001, 1000, -647},
      {__LINE__, s_rem, 5, 2, 1},
      {__LINE__, s_rem, -5, 2, -1},
      {__LINE__, s_rem, 5, -2, 1},
      {__LINE__, s_rem, -5, -2, -1},
      {__LINE__, s_rem, 7, 3, 1},
      {__LINE__, s_rem, -7, 3, -1},
      {__LINE__, s_rem, 7, -3, 1},
      {__LINE__, s_rem, -7, -3, -1},
      {__LINE__, s_rem, 11, 5, 1},
      {__LINE__, s_rem, 17, 7, 3},
      {__LINE__, u_rem, 1, 1, 0},
      {__LINE__, u_rem, 0, 1, 0},
      {__LINE__, u_rem, -1, -1, 0},
      {__LINE__, u_rem, 0x80000000, -1, 0x80000000},
      {__LINE__, u_rem, 0x80000000, 2, 0},
      {__LINE__, u_rem, 0x8ff00ff0, 0x10001, 0x8001},
      {__LINE__, u_rem, 0x80000001, 1000, 649},
      {__LINE__, u_rem, 5, 2, 1},
      {__LINE__, u_rem, -5, 2, 1},
      {__LINE__, u_rem, 5, -2, 5},
      {__LINE__, u_rem, -5, -2, -5},
      {__LINE__, u_rem, 7, 3, 1},
      {__LINE__, u_rem, 11, 5, 1},
      {__LINE__, u_rem, 17, 7, 3},
      {__LINE__, u_and, 1, 0, 0},
      {__LINE__, u_and, 0, 1, 0},
      {__LINE__, u_and, 1, 1, 1},
      {__LINE__, u_and, 0, 0, 0},
      {__LINE__, u_and, 0x7fffffff, 0x80000000, 0},
      {__LINE__, u_and, 0x7fffffff, -1, 0x7fffffff},
      {__LINE__, u_and, 0xf0f0ffff, 0xfffff0f0, 0xf0f0f0f0},
      {__LINE__, u_and, 0xffffffff, 0xffffffff, 0xffffffff},
      {__LINE__, u_or, 1, 0, 1},
      {__LINE__, u_or, 0, 1, 1},
      {__LINE__, u_or, 1, 1, 1},
      {__LINE__, u_or, 0, 0, 0},
      {__LINE__, u_or, 0x7fffffff, 0x80000000, -1},
      {__LINE__, u_or, 0x80000000, 0, 0x80000000},
      {__LINE__, u_or, 0xf0f0ffff, 0xfffff0f0, 0xffffffff},
      {__LINE__, u_or, 0xffffffff, 0xffffffff, 0xffffffff},
      {__LINE__, u_xor, 1, 0, 1},
      {__LINE__, u_xor, 0, 1, 1},
      {__LINE__, u_xor, 1, 1, 0},
      {__LINE__, u_xor, 0, 0, 0},
      {__LINE__, u_xor, 0x7fffffff, 0x80000000, -1},
      {__LINE__, u_xor, 0x80000000, 0, 0x80000000},
      {__LINE__, u_xor, -1, 0x80000000, 0x7fffffff},
      {__LINE__, u_xor, -1, 0x7fffffff, 0x80000000},
      {__LINE__, u_xor, 0xf0f0ffff, 0xfffff0f0, 0x0f0f0f0f},
      {__LINE__, u_xor, 0xffffffff, 0xffffffff, 0},
      {__LINE__, u_shl, 1, 1, 2},
      {__LINE__, u_shl, 1, 0, 1},
      {__LINE__, u_shl, 0x7fffffff, 1, 0xfffffffe},
      {__LINE__, u_shl, 0xffffffff, 1, 0xfffffffe},
      {__LINE__, u_shl, 0x80000000, 1, 0},
      {__LINE__, u_shl, 0x40000000, 1, 0x80000000},
      {__LINE__, u_shl, 1, 31, 0x80000000},
      {__LINE__, u_shl, 1, 32, 1},
      {__LINE__, u_shl, 1, 33, 2},
      {__LINE__, u_shl, 1, -1, 0x80000000},
      {__LINE__, u_shl, 1, 0x7fffffff, 0x80000000},
      {__LINE__, s_shr, 1, 1, 0},
      {__LINE__, s_shr, 1, 0, 1},
      {__LINE__, s_shr, -1, 1, -1},
      {__LINE__, s_shr, 0x7fffffff, 1, 0x3fffffff},
      {__LINE__, s_shr, 0x80000000, 1, 0xc0000000},
      {__LINE__, s_shr, 0x40000000, 1, 0x20000000},
      {__LINE__, s_shr, 1, 32, 1},
      {__LINE__, s_shr, 1, 33, 0},
      {__LINE__, s_shr, 1, -1, 0},
      {__LINE__, s_shr, 1, 0x7fffffff, 0},
      {__LINE__, s_shr, 1, 0x80000000, 1},
      {__LINE__, s_shr, 0x80000000, 31, -1},
      {__LINE__, s_shr, -1, 32, -1},
      {__LINE__, s_shr, -1, 33, -1},
      {__LINE__, s_shr, -1, -1, -1},
      {__LINE__, s_shr, -1, 0x7fffffff, -1},
      {__LINE__, s_shr, -1, 0x80000000, -1},
      {__LINE__, u_shr, 1, 1, 0},
      {__LINE__, u_shr, 1, 0, 1},
      {__LINE__, u_shr, -1, 1, 0x7fffffff},
      {__LINE__, u_shr, 0x7fffffff, 1, 0x3fffffff},
      {__LINE__, u_shr, 0x80000000, 1, 0x40000000},
      {__LINE__, u_shr, 0x40000000, 1, 0x20000000},
      {__LINE__, u_shr, 1, 32, 1},
      {__LINE__, u_shr, 1, 33, 0},
      {__LINE__, u_shr, 1, -1, 0},
      {__LINE__, u_shr, 1, 0x7fffffff, 0},
      {__LINE__, u_shr, 1, 0x80000000, 1},
      {__LINE__, u_shr, 0x80000000, 31, 1},
      {__LINE__, u_shr, -1, 32, -1},
      {__LINE__, u_shr, -1, 33, 0x7fffffff},
      {__LINE__, u_shr, -1, -1, 1},
      {__LINE__, u_shr, -1, 0x7fffffff, 1},
      {__LINE__, u_shr, -1, 0x80000000, -1},
      {__LINE__, u_rotl, 1, 1, 2},
      {__LINE__, u_rotl, 1, 0, 1},
      {__LINE__, u_rotl, -1, 1, -1},
      {__LINE__, u_rotl, 1, 32, 1},
      {__LINE__, u_rotl, 0xabcd9876, 1, 0x579b30ed},
      {__LINE__, u_rotl, 0xfe00dc00, 4, 0xe00dc00f},
      {__LINE__, u_rotl, 0xb0c1d2e3, 5, 0x183a5c76},
      {__LINE__, u_rotl, 0x00008000, 37, 0x00100000},
      {__LINE__, u_rotl, 0xb0c1d2e3, 0xff05, 0x183a5c76},
      {__LINE__, u_rotl, 0x769abcdf, 0xffffffed, 0x579beed3},
      {__LINE__, u_rotl, 0x769abcdf, 0x8000000d, 0x579beed3},
      {__LINE__, u_rotl, 1, 31, 0x80000000},
      {__LINE__, u_rotl, 0x80000000, 1, 1},
      {__LINE__, u_rotr, 1, 1, 0x80000000},
      {__LINE__, u_rotr, 1, 0, 1},
      {__LINE__, u_rotr, -1, 1, -1},
      {__LINE__, u_rotr, 1, 32, 1},
      {__LINE__, u_rotr, 0xff00cc00, 1, 0x7f806600},
      {__LINE__, u_rotr, 0x00080000, 4, 0x00008000},
      {__LINE__, u_rotr, 0xb0c1d2e3, 5, 0x1d860e97},
      {__LINE__, u_rotr, 0x00008000, 37, 0x00000400},
      {__LINE__, u_rotr, 0xb0c1d2e3, 0xff05, 0x1d860e97},
      {__LINE__, u_rotr, 0x769abcdf, 0xffffffed, 0xe6fbb4d5},
      {__LINE__, u_rotr, 0x769abcdf, 0x8000000d, 0xe6fbb4d5},
      {__LINE__, u_rotr, 1, 31, 2},
      {__LINE__, u_rotr, 0x80000000, 31, 1},
  };
  static const struct data4 d4[] = {
      {__LINE__, u_eq, 0, 0, 1},
      {__LINE__, u_eq, 1, 1, 1},
      {__LINE__, u_eq, -1, 1, 0},
      {__LINE__, u_eq, 0x80000000, 0x80000000, 1},
      {__LINE__, u_eq, 0x7fffffff, 0x7fffffff, 1},
      {__LINE__, u_eq, -1, -1, 1},
      {__LINE__, u_eq, 1, 0, 0},
      {__LINE__, u_eq, 0, 1, 0},
      {__LINE__, u_eq, 0x80000000, 0, 0},
      {__LINE__, u_eq, 0, 0x80000000, 0},
      {__LINE__, u_eq, 0x80000000, -1, 0},
      {__LINE__, u_eq, -1, 0x80000000, 0},
      {__LINE__, u_eq, 0x80000000, 0x7fffffff, 0},
      {__LINE__, u_eq, 0x7fffffff, 0x80000000, 0},
      {__LINE__, u_ne, 0, 0, 0},
      {__LINE__, u_ne, 1, 1, 0},
      {__LINE__, u_ne, -1, 1, 1},
      {__LINE__, u_ne, 0x80000000, 0x80000000, 0},
      {__LINE__, u_ne, 0x7fffffff, 0x7fffffff, 0},
      {__LINE__, u_ne, -1, -1, 0},
      {__LINE__, u_ne, 1, 0, 1},
      {__LINE__, u_ne, 0, 1, 1},
      {__LINE__, u_ne, 0x80000000, 0, 1},
      {__LINE__, u_ne, 0, 0x80000000, 1},
      {__LINE__, u_ne, 0x80000000, -1, 1},
      {__LINE__, u_ne, -1, 0x80000000, 1},
      {__LINE__, u_ne, 0x80000000, 0x7fffffff, 1},
      {__LINE__, u_ne, 0x7fffffff, 0x80000000, 1},
      {__LINE__, s_lt, 0, 0, 0},
      {__LINE__, s_lt, 1, 1, 0},
      {__LINE__, s_lt, -1, 1, 1},
      {__LINE__, s_lt, 0x80000000, 0x80000000, 0},
      {__LINE__, s_lt, 0x7fffffff, 0x7fffffff, 0},
      {__LINE__, s_lt, -1, -1, 0},
      {__LINE__, s_lt, 1, 0, 0},
      {__LINE__, s_lt, 0, 1, 1},
      {__LINE__, s_lt, 0x80000000, 0, 1},
      {__LINE__, s_lt, 0, 0x80000000, 0},
      {__LINE__, s_lt, 0x80000000, -1, 1},
      {__LINE__, s_lt, -1, 0x80000000, 0},
      {__LINE__, s_lt, 0x80000000, 0x7fffffff, 1},
      {__LINE__, s_lt, 0x7fffffff, 0x80000000, 0},
      {__LINE__, u_lt, 0, 0, 0},
      {__LINE__, u_lt, 1, 1, 0},
      {__LINE__, u_lt, -1, 1, 0},
      {__LINE__, u_lt, 0x80000000, 0x80000000, 0},
      {__LINE__, u_lt, 0x7fffffff, 0x7fffffff, 0},
      {__LINE__, u_lt, -1, -1, 0},
      {__LINE__, u_lt, 1, 0, 0},
      {__LINE__, u_lt, 0, 1, 1},
      {__LINE__, u_lt, 0x80000000, 0, 0},
      {__LINE__, u_lt, 0, 0x80000000, 1},
      {__LINE__, u_lt, 0x80000000, -1, 1},
      {__LINE__, u_lt, -1, 0x80000000, 0},
      {__LINE__, u_lt, 0x80000000, 0x7fffffff, 0},
      {__LINE__, u_lt, 0x7fffffff, 0x80000000, 1},
      {__LINE__, s_le, 0, 0, 1},
      {__LINE__, s_le, 1, 1, 1},
      {__LINE__, s_le, -1, 1, 1},
      {__LINE__, s_le, 0x80000000, 0x80000000, 1},
      {__LINE__, s_le, 0x7fffffff, 0x7fffffff, 1},
      {__LINE__, s_le, -1, -1, 1},
      {__LINE__, s_le, 1, 0, 0},
      {__LINE__, s_le, 0, 1, 1},
      {__LINE__, s_le, 0x80000000, 0, 1},
      {__LINE__, s_le, 0, 0x80000000, 0},
      {__LINE__, s_le, 0x80000000, -1, 1},
      {__LINE__, s_le, -1, 0x80000000, 0},
      {__LINE__, s_le, 0x80000000, 0x7fffffff, 1},
      {__LINE__, s_le, 0x7fffffff, 0x80000000, 0},
      {__LINE__, u_le, 0, 0, 1},
      {__LINE__, u_le, 1, 1, 1},
      {__LINE__, u_le, -1, 1, 0},
      {__LINE__, u_le, 0x80000000, 0x80000000, 1},
      {__LINE__, u_le, 0x7fffffff, 0x7fffffff, 1},
      {__LINE__, u_le, -1, -1, 1},
      {__LINE__, u_le, 1, 0, 0},
      {__LINE__, u_le, 0, 1, 1},
      {__LINE__, u_le, 0x80000000, 0, 0},
      {__LINE__, u_le, 0, 0x80000000, 1},
      {__LINE__, u_le, 0x80000000, -1, 1},
      {__LINE__, u_le, -1, 0x80000000, 0},
      {__LINE__, u_le, 0x80000000, 0x7fffffff, 0},
      {__LINE__, u_le, 0x7fffffff, 0x80000000, 1},
      {__LINE__, s_gt, 0, 0, 0},
      {__LINE__, s_gt, 1, 1, 0},
      {__LINE__, s_gt, -1, 1, 0},
      {__LINE__, s_gt, 0x80000000, 0x80000000, 0},
      {__LINE__, s_gt, 0x7fffffff, 0x7fffffff, 0},
      {__LINE__, s_gt, -1, -1, 0},
      {__LINE__, s_gt, 1, 0, 1},
      {__LINE__, s_gt, 0, 1, 0},
      {__LINE__, s_gt, 0x80000000, 0, 0},
      {__LINE__, s_gt, 0, 0x80000000, 1},
      {__LINE__, s_gt, 0x80000000, -1, 0},
      {__LINE__, s_gt, -1, 0x80000000, 1},
      {__LINE__, s_gt, 0x80000000, 0x7fffffff, 0},
      {__LINE__, s_gt, 0x7fffffff, 0x80000000, 1},
      {__LINE__, u_gt, 0, 0, 0},
      {__LINE__, u_gt, 1, 1, 0},
      {__LINE__, u_gt, -1, 1, 1},
      {__LINE__, u_gt, 0x80000000, 0x80000000, 0},
      {__LINE__, u_gt, 0x7fffffff, 0x7fffffff, 0},
      {__LINE__, u_gt, -1, -1, 0},
      {__LINE__, u_gt, 1, 0, 1},
      {__LINE__, u_gt, 0, 1, 0},
      {__LINE__, u_gt, 0x80000000, 0, 1},
      {__LINE__, u_gt, 0, 0x80000000, 0},
      {__LINE__, u_gt, 0x80000000, -1, 0},
      {__LINE__, u_gt, -1, 0x80000000, 1},
      {__LINE__, u_gt, 0x80000000, 0x7fffffff, 1},
      {__LINE__, u_gt, 0x7fffffff, 0x80000000, 0},
      {__LINE__, s_ge, 0, 0, 1},
      {__LINE__, s_ge, 1, 1, 1},
      {__LINE__, s_ge, -1, 1, 0},
      {__LINE__, s_ge, 0x80000000, 0x80000000, 1},
      {__LINE__, s_ge, 0x7fffffff, 0x7fffffff, 1},
      {__LINE__, s_ge, -1, -1, 1},
      {__LINE__, s_ge, 1, 0, 1},
      {__LINE__, s_ge, 0, 1, 0},
      {__LINE__, s_ge, 0x80000000, 0, 0},
      {__LINE__, s_ge, 0, 0x80000000, 1},
      {__LINE__, s_ge, 0x80000000, -1, 0},
      {__LINE__, s_ge, -1, 0x80000000, 1},
      {__LINE__, s_ge, 0x80000000, 0x7fffffff, 0},
      {__LINE__, s_ge, 0x7fffffff, 0x80000000, 1},
      {__LINE__, u_ge, 0, 0, 1},
      {__LINE__, u_ge, 1, 1, 1},
      {__LINE__, u_ge, -1, 1, 1},
      {__LINE__, u_ge, 0x80000000, 0x80000000, 1},
      {__LINE__, u_ge, 0x7fffffff, 0x7fffffff, 1},
      {__LINE__, u_ge, -1, -1, 1},
      {__LINE__, u_ge, 1, 0, 1},
      {__LINE__, u_ge, 0, 1, 0},
      {__LINE__, u_ge, 0x80000000, 0, 1},
      {__LINE__, u_ge, 0, 0x80000000, 0},
      {__LINE__, u_ge, 0x80000000, -1, 0},
      {__LINE__, u_ge, -1, 0x80000000, 1},
      {__LINE__, u_ge, 0x80000000, 0x7fffffff, 1},
      {__LINE__, u_ge, 0x7fffffff, 0x80000000, 0},
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
