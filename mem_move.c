#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "test.h"

#define MEM_SIZE 32
#define VIRTUAL_STARTING_LOCATION 100

/*
 * Please Read!
 *
 * Approach:
 *   I create a structure which contains:
 *     1) a block of char array acts as a memory
 *     2) a virtual location starting at VIRTUAL_STARTING_LOCATION
 *   And implementing the following functions for accessing:
 *     a) prep(): 
 *          constructor (sort of)
 *     b) flush_mem(): 
 *          flush char array w/ spaces (easier for debug)
 *     c) get_pointer_at_specific_loc():
 *          request a char pointer at a specific location
 *     d) write():
 *          write content into memory
 *     e) request_available_mem():
 *          called by memmove_(); find and return a char pointer with
 *          a enough length
 *
 *  memmove_ function:
 *    first, determine the gap between source and destination. If the gap
 *    is not big enough, then pass "source" and "length" to
 *    "request_available_mem()" in order to assign a big-enough memory to
 *    destination pointer.
 *    second, copying one by one.
 *    [NOTE] Does not need to clear the content pointed by "source" b/c
 *           we can simply overwrite it later on
 *
 *  [More Thoughts]
 *    It'd be easier to implement a "circular array" for memmove but it'd
 *    be a little bit less efficient on "read" operation.
 */

void flush_mem();

struct MemManagement{
  char anchor[MEM_SIZE];
  unsigned int mem_start_loc;
} mem_manager;


void prep(){
  // Set up virtual memory block
  mem_manager.mem_start_loc = VIRTUAL_STARTING_LOCATION;

  flush_mem();
}

void flush_mem(){
  int idx = 0;
  for(idx; idx < MEM_SIZE - 1; idx++){
    mem_manager.anchor[idx] = ' ';
  }

  mem_manager.anchor[MEM_SIZE - 1] = '\0';
}

char *get_pointer_at_specific_loc(unsigned int rLoc){
  char *runner = mem_manager.anchor;
  int idx = 0;

  for(idx; idx<(rLoc - mem_manager.mem_start_loc); idx++){
    runner++;
  }

  return runner;
}

char *write(unsigned int loc, char *content, unsigned int length){
  // [TODO] check if the value of loc is within 0 and MEM_SIZE
  if(loc < mem_manager.mem_start_loc){
    return NULL;
  }
  if((loc - mem_manager.mem_start_loc) > MEM_SIZE){
    return NULL;
  }
  if(loc + length > mem_manager.mem_start_loc + MEM_SIZE){
    return NULL;
  }
  // END TODO

  char *ret = mem_manager.anchor + loc - mem_manager.mem_start_loc;
  char *runner = ret;

  while(length){
    *runner++ = *content++;
    length--;
  }

  return ret;
}

char *request_available_mem(const char *source, uint32_t len){
  char *s_ = source;
  unsigned int source_begin = mem_manager.mem_start_loc + (
        source - mem_manager.anchor
      );
  if(MEM_SIZE - (source_begin + len) > len){
    // If the memory block after source string is big enough
    return s_ + len + 1;
  }
  else if(source_begin > len){
    return mem_manager.anchor;
  }  
}

char *memmove_(const char *source, char *dest, uint32_t length){
  uint32_t gap = ((dest - source) > 0)? (dest - source): (source - dest);

  if(gap < length){
    // The gap b/w two pointers are not big enough
    dest = request_available_mem(source, length);
  }

  char *from = source;
  char *to   = dest;

  while(length){
    *to++ = *from++;
    length--;
  } // end while

  return dest;
}

void test_0(){
  // testing if the content of both pointers have the same value
  char input[] = "abcde";
  unsigned int length = 5;
  unsigned int e_loc = 102;
  unsigned int r_loc = 100;

  char *source = write(e_loc, input, length);
  char *destination = get_pointer_at_specific_loc(r_loc);
  destination = memmove_(source, destination, length);

  printf("CASE: \"%s == %s\"\n", input, input);
  ASSERT_EQ_VALUE(source, destination, length);
}

void test_1(){
  // testing if the locations of both pointers are the same
  char input[] = "abcde";
  unsigned int length = 5;
  unsigned int e_loc = 102;
  unsigned int r_loc = 100;

  char *source = write(e_loc, input, length);
  char *destination = get_pointer_at_specific_loc(r_loc);
  destination = memmove_(source, destination, length);

  unsigned int dest_loc = destination -
                          mem_manager.anchor +
                          mem_manager.mem_start_loc;

  printf("CASE: \"%d == %d\"\n", e_loc, dest_loc);
  ASSERT_DIFF_LOC(source, destination);
}

void test_2(){
  // testing locations directly [fail case]
  // source : 102
  // dest : 100
  char input[] = "abcde";
  unsigned int length = 5;
  unsigned int e_loc = 102;
  unsigned int r_loc = 100;

  char *source = write(e_loc, input, length);
  char *destination = get_pointer_at_specific_loc(r_loc);
  destination = memmove_(source, destination, length);

  uint32_t str_loc = destination - 
                     mem_manager.anchor + 
                     mem_manager.mem_start_loc;

  printf("CASE: \"%d == %d\"\n", r_loc, str_loc);
  ASSERT_LOC(r_loc, str_loc);
}

void test_3(){
  // testing locations directly [fail case]
  // source : 100
  // dest : 102
  char input[] = "abcde";
  unsigned int length = 5;
  unsigned int e_loc = 100;
  unsigned int r_loc = 102;

  char *source = write(e_loc, input, length);
  char *destination = get_pointer_at_specific_loc(r_loc);
  destination = memmove_(source, destination, length);

  uint32_t str_loc = destination - 
                     mem_manager.anchor + 
                     mem_manager.mem_start_loc;

  printf("CASE: \"%d == %d\"\n", r_loc, str_loc);
  ASSERT_LOC(r_loc, str_loc);
}

void all_tests(){
  test_0();
  test_1();
  test_2();
}

int main(){
  prep();

  // testing
  all_tests();
  printf("-------------------------------\n");
  printf("Number of tested cases: %d\n", num_tests_ran);
  printf("\t[pass]: %d\n", pass_cases);
  printf("\t[fail]: %d\n", fail_cases);

  return 0;
}
