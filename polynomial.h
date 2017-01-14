#include <stdbool.h>
struct term
{
    int coeff;
    unsigned int exp;
    struct term *next;
};
typedef struct term polynomial;


struct term *term_create(
    int coeff,
    int exp);

void poly_destroy(
    polynomial * eqn);

void poly_print(
    polynomial * eqn);

polynomial *simplify(
    polynomial * p);

void pp(
    polynomial * a);

void poly_iterate(
    polynomial * p,
    void (*transform) (struct term *));

polynomial *poly_add(
    polynomial * a,
    polynomial * b);

polynomial *poly_sub(
    polynomial * a,
    polynomial * b);

char *poly_to_string(
    polynomial * p);

bool poly_equal(
    polynomial * a,
    polynomial * b);

void poly_sort(
    polynomial ** p);

double poly_eval(
    polynomial * p,
    double x);

polynomial *poly_mult(
    polynomial * a,
    polynomial * b);
    
    polynomial *
poly_div(
    polynomial * a,
    polynomial * b);
