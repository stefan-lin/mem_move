#include <stdio.h>
#include <stdint.h>

void ASSERT_EQ_VALUE(char *expect, char *recieve, uint32_t len);
void ASSERT_DIFF_LOC(char *expect, char *recieve);
void ASSERT_LOC(uint32_t expect_loc, uint32_t str_loc);

unsigned int num_tests_ran;
unsigned int fail_cases;
unsigned int pass_cases;

void ASSERT_EQ_VALUE(char *expect, char *recieve, uint32_t len){
  do{
    unsigned int idx = 0;
    unsigned int result_flag = 1;

    for(idx; idx < len; idx++){
      if(expect[idx] != recieve[idx]){
        result_flag = 0;
        break;
      }
    } // END FOR
    
    num_tests_ran++;
    if(result_flag){
      pass_cases++;
      printf("\t[PASS]\n");
    }
    else{
      fail_cases++;
      printf("\t[FAIL]\n");
    }
  } while(0);
}

void ASSERT_DIFF_LOC(char *expect, char *recieve){
  do{
    if(!(expect - recieve)){
      fail_cases++;
      printf("\t[FAIL]\n");
    }
    else{
      pass_cases++;
      printf("\t[PASS]\n");
    }
    num_tests_ran++;
  } while(0);
}

void ASSERT_LOC(uint32_t expect_loc, uint32_t str_loc){
  do{
    if(expect_loc == str_loc){
      pass_cases++;
      printf("\t[PASS]\n");
    }
    else{
      fail_cases++;
      printf("\t[FAIL]\n");
    }
    num_tests_ran++;
  } while(0);
}
