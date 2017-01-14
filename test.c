#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "polynomial.h"

int
main(
    void)
{
    polynomial *first = term_create(3, 3);
    polynomial *second = term_create(5, 2);
    polynomial *third = term_create(1, 0);

    first->next = second;
    second->next = third;

    polynomial *a = term_create(4, 1);
    polynomial *b = term_create(12, 3);
    polynomial *c = term_create(19, 5);

    //polynomial *d = term_create(4, 1);
    //polynomial *e = term_create(3, 0);

    a->next = b;
    b->next = c;
    //c->next = d;
    //d->next = e;
    puts("pre sort~~");
    poly_sort(&a);
    puts("a1");
    poly_print(a);
    puts("~~post sort");
    //simplify(&a);
    polynomial *sum = poly_sub(first, a);

    poly_print(sum);
    puts("");
    //simplify(&a);
    poly_print(a);
    puts("");
    poly_equal(a, a);
    char *result = (poly_to_string(first));

    printf("\nresult: %s\n", result);

    poly_iterate(a, pp);
    printf("eval: %lf\n", poly_eval(first, 2));
    puts("a2");
    poly_print(a);

    polynomial *mult = poly_mult(first, a);
    puts("\n\n~~~~~~~~~~~~~~~");
    poly_print(first);
    puts("");
    poly_print(a);
    puts("");
    poly_print(mult);
    puts("\n~~~~~~~~~~~~~~~");


    polynomial *one = term_create(21, 3);
    polynomial *two = term_create(-35, 2);
    polynomial *three = term_create(7, 1);
    one->next = two;
    polynomial *div = poly_div(one, three);
    puts("\n\n~~~~~~~~~~~~~~~");
    poly_print(first);
    puts("");
    poly_print(a);
    puts("");
    poly_print(div);
    puts("\n~~~~~~~~~~~~~~~");



    poly_destroy(mult);
    poly_destroy(first);
    poly_destroy(a);
    poly_destroy(sum);
    free(result);
    puts("");
}
