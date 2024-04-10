#include <assert.h>
#include <stdlib.h>

#include <crs_matrix.h>
#include <matops.h>
#include <vector.h>

#define LOAD_MATRIX(stream) load_crs_matrix(stream)
#define SYM_CHECK(m_) crs_is_symmetric(m_)
#define DUMP_MATRIX(stream, m_) dump_crs_matrix(stream, m_)
#define MAT_MULT_SYMM crs_symm_vect_mult
#define MAT_MULT crs_vect_mult
#define GET_MATRIX_SIZE(m) get_crs_matrix_size(m)
#define DESTROY_MATRIX(m) destroy_crs_matrix(m)
#define SWAP_FUNCTION(d, s, p)
#define MAT_SHUFFLE_ARRAY(m)

typedef struct crs_matrix s_matrix;
typedef struct vector *(*mat_vect_mult_fn)(const struct crs_matrix *,
                                           const struct vector *,
                                           struct vector *);

int main(void) {
  s_matrix *m = LOAD_MATRIX(stdin);
  mat_vect_mult_fn mat_mult_fn;

  assert(m != NULL);
  size_t col = GET_MATRIX_SIZE(m);
  struct vector *v = make_col_ones(col);
  struct vector *r = make_col_ones(col);
  struct vector *s __attribute__((unused)) = make_col_ones(col);
  struct vector *t;
  assert(v != NULL);
  assert(r != NULL);

  DUMP_MATRIX(stdout, m);
  if (SYM_CHECK(m)) {
    mat_mult_fn = MAT_MULT_SYMM;
  } else {
    mat_mult_fn = MAT_MULT;
  }

  dump_vector(stdout, v);
  dump_vector(stdout, r);

  for (size_t iter = 0; iter < 10; iter++) {
    fprintf(stdout, "[+] iteration: %zu\n", iter);
    SWAP_FUNCTION(s, v, MAT_SHUFFLE_ARRAY(m));
    t = mat_mult_fn(m, v, r);
    assert(r == t);
    dump_vector(stdout, t);
    r = v;
    v = t;
  }

  DESTROY_MATRIX(m);
  destroy_vector(v);
  destroy_vector(r);
  destroy_vector(s);

  return EXIT_SUCCESS;
}
