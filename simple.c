#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "test.h"

void test_0(){
  char e[6] = "abcde\0";
  char r[6] = "abcde\0";

  printf("CASE: \"%s == %s\"\n", e, r);
  ASSERT_EQ_VALUE(e, r, 5);
}

int main(){
  test_0();

  printf("------------------------------------------------------------\n");
  printf("Number of tested cases: %d\n", num_tests_ran);
  printf("\t[pass]: %d\n", pass_cases);
  printf("\t[fail]: %d\n", fail_cases);
}
