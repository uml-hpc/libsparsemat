#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <cpu.h>

int main(void) {
  char buf[1024] = {0};
  get_cpu_name(buf);
  fprintf(stdout, "%s\n", buf);
  fprintf(stdout, "CPU %ssupports rtdscp\n",
          cpu_has_rtdscp() ? "" : "does not ");
  fprintf(stdout, "CPU %ssupports rtdsc\n", cpu_has_rtdsc() ? "" : "does not ");
  fprintf(stdout, "CPU %ssupports TSX\n", cpu_has_tsx() ? "" : "does not ");

  return EXIT_SUCCESS;
}
