#include <assert.h>
#include <stdlib.h>

#include <vector.h>

int main(void) {
  struct vector *v;
  v = make_col_ones(32);

  assert(v != NULL);
  dump_vector(stdout, v);

  destroy_vector(v);
  return EXIT_SUCCESS;
}
