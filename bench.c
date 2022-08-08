#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{
 
  int result;
  struct timespec tp;
  clockid_t clk_id;
  int len = 100000;
  long results[len];

  // clk_id = CLOCK_BOOTTIME;
  // clk_id = CLOCK_MONOTONIC;
  clk_id = CLOCK_REALTIME;

  long longest = 0;
  long over_milli = 0;

  result = clock_getres(clk_id, &tp);
  printf("result: %i\n", result);
  printf("resolution of tp.tv_sec: %ld\n", tp.tv_sec);
  printf("resolution of tp.tv_nsec in nanoseconds: %ld\n", tp.tv_nsec);
  printf("------- showing results in microseconds\n");

  while (1){
    for(int i = 0; i < len; i++){
      result = clock_gettime(clk_id, &tp);
      results[i] = tp.tv_nsec/1000;
    }

    long last = results[0];
    for(int i = 1; i < len; i++){
      long gap = results[i] - last;
      if(gap > 1000){
        over_milli++;
        printf("found a gap over a millisecond, that's our %ldth (%ld microseconds)\n", over_milli, gap/1000);
      }

      if(gap > longest){
        longest = gap;
        printf("found a new longest gap! %ld microseconds - %ld -> %ld\n", gap, last, results[i]);
      }
      last = results[i];
    }
  }
}
