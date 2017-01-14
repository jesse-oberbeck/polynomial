#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "polynomial.h"

struct term *
term_create(
    int coeff,
    int exp)
{
    struct term *node = malloc(sizeof(*node));

    if (node)
    {
        node->coeff = coeff;
        node->exp = exp;
        node->next = NULL;
    }
    return node;
}

void
poly_destroy(
    polynomial * eqn)
{
    while (eqn)
    {
        struct term *tmp = eqn->next;

        free(eqn);
        eqn = tmp;
    }
}

void
poly_print(
    polynomial * eqn)
{
    if (!eqn)
    {
        return;
    }
    if (eqn->coeff)
    {
        printf("%c%d", eqn->coeff > 0 ? '+' : '\0', eqn->coeff);
        if (eqn->exp > 1)
        {
            printf("x^%d", eqn->exp);
        }
        else if (eqn->exp == 1)
        {
            printf("x");
        }
        printf(" ");
    }
    poly_print(eqn->next);
}

///////////////////////////////////////////////
polynomial *
poly_mult(
    polynomial * a,
    polynomial * b)
{
    //Multiplies polynomials a and b by finding the product
    //of every pair of coefficients, and the sum of every
    //pair of exponents, then sorting and reducing the pairs.
    int count = 0;
    polynomial *mult = term_create(0, 0);
    polynomial *first = mult;
    polynomial *firstB = b;

    while (a != NULL)
    {
        while (b != NULL)
        {
            count += 1;
            mult->coeff = a->coeff * b->coeff;
            mult->exp = a->exp + b->exp;
            b = b->next;
            mult->next = term_create(0, 0);
            mult = mult->next;
        }
        a = a->next;
        b = firstB;
    }
    printf("COUNT: %d\n", count);
    poly_sort(&first);
    simplify(first);
    return (first);
}

polynomial *
poly_div(
    polynomial * a,
    polynomial * b)
{
    //Divides polynomials a and b by finding the quotient
    //of every pair of coefficients, and the difference of every
    //pair of exponents, then sorting and reducing the pairs.
    int count = 0;
    polynomial *mult = term_create(0, 0);
    polynomial *first = mult;
    polynomial *firstB = b;

    while (a != NULL)
    {
        while (b != NULL)
        {
            count += 1;
            mult->coeff = a->coeff / b->coeff;
            mult->exp = a->exp - b->exp;
            b = b->next;
            mult->next = term_create(0, 0);
            mult = mult->next;
        }
        a = a->next;
        b = firstB;
    }
    printf("COUNT: %d\n", count);
    poly_sort(&first);
    simplify(first);
    return (first);
}

polynomial *
simplify(
    polynomial * p)
{
    //Reduces a polynomial to less terms by finding the sum
    //of terms with matching exponents.
    polynomial *front = p;
    polynomial *cursor;

    cursor = p;
    while (cursor->next != NULL)
    {
        if (cursor->exp == cursor->next->exp)
        {
            cursor->coeff = cursor->coeff + cursor->next->coeff;
            polynomial *temp = cursor->next;

            cursor->next = cursor->next->next;
            free(temp);
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return (front);
}

void
pp(
    polynomial * a)
{
    //This function exists only to test poly_iterate.
    printf("TERM COEF: %d\n", a->coeff);
}

void
poly_iterate(
    polynomial * p,
    void (*transform) (struct term *))
{
    //Sends every node of a polynomial linked list to
    //the function passed to this function as transform.
    while (p != NULL)
    {
        transform(p);
        p = p->next;
    }
}

polynomial *
poly_add(
    polynomial * a,
    polynomial * b)
{
    //Finds the sum of two polynomial linked lists.
    //by scrolling through both sets at the same time
    //and adding together those with like exponents.
    simplify(a);
    simplify(b);
    polynomial *sum = term_create(0, 0);
    polynomial *cursor = sum;

    while (a && b)
    {
        //If the coefficients are equal, add them together.
        if (a->exp == b->exp)
        {
            cursor->exp = a->exp;
            cursor->coeff = (a->coeff + b->coeff);
            a = a->next;
            b = b->next;
        }
        //If a is larger give it it's own node, and advance the pointer.
        else if (a->exp > b->exp)
        {
            cursor->exp = a->exp;
            cursor->coeff = a->coeff;
            a = a->next;
        }
        //If b is larger give it it's own node, and advance the pointer.
        else if (a->exp < b->exp)
        {
            cursor->exp = b->exp;
            cursor->coeff = b->coeff;
            b = b->next;
        }
        //Build the next blank term before looping.
        cursor->next = term_create(0, 0);
        cursor = cursor->next;
    }
    return (sum);
}


polynomial *
poly_sub(
    polynomial * a,
    polynomial * b)
{
    //Finds the difference between two polynomial linked lists.
    //by scrolling through both sets at the same time
    //and subtracting those with like exponents.
    simplify(a);
    simplify(b);
    polynomial *sum = term_create(0, 0);
    polynomial *cursor = sum;

    while (a && b)
    {
        //If the coefficients are equal, remove one from the other.
        if (a->exp == b->exp)
        {
            cursor->exp = a->exp;
            cursor->coeff = (a->coeff - b->coeff);
            a = a->next;
            b = b->next;
        }
        //If a is larger give it it's own node, and advance the pointer.
        else if (a->exp > b->exp)
        {
            cursor->exp = a->exp;
            cursor->coeff = a->coeff;
            a = a->next;
        }
        //If b is larger give it it's own node, and advance the pointer.
        else if (a->exp < b->exp)
        {
            cursor->exp = b->exp;
            cursor->coeff = b->coeff * -1;
            b = b->next;
        }
        //Build the next blank term before looping.
        cursor->next = term_create(0, 0);
        cursor = cursor->next;
    }
    return (sum);
}


char *
poly_to_string(
    polynomial * p)
{
    //Cyclically adds each term to a buffer using the logic
    //from poly_print, and sprintf. I would have just used
    //snprintf on poly_print, except it had to be a void
    //function...
    polynomial *cursor = p;
    char *buffer = calloc(42, 1);

    while (cursor != NULL)
    {
        if (!cursor)
        {
            sprintf(buffer, "Nothing");
            return (buffer);
        }
        if (cursor->coeff)
        {
            sprintf(buffer, "%s%c%d", buffer, cursor->coeff > 0 ? '+' : '\0',
                    cursor->coeff);
            if (cursor->exp > 1)
            {
                sprintf(buffer, "%sx^%d ", buffer, cursor->exp);
            }
            else if (cursor->exp == 1)
            {
                sprintf(buffer, "%sx ", buffer);
            }
            printf(" ");
        }
        cursor = cursor->next;
    }
    return (buffer);
}

bool
poly_equal(
    polynomial * a,
    polynomial * b)
{
    while (a != NULL)
    {
        //Checks values for equality after first checking if b exists.
        //Only checks on b because if one exists and the other doesn't
        //the polynomials clearly aren't equal.
        if ((b == NULL) || (a->exp != b->exp) || (a->coeff != b->coeff))
        {
            puts("false");
            return (false);
        }
        a = a->next;
        b = b->next;
    }
    puts("true");
    return (true);
}

void
poly_sort(
    polynomial ** p)
{
    //Ugly bubble sort, but it's better than a Bogo sort,
    //and a merge sort is only slightly better,
    //and much more difficult to implement.
    polynomial *front = *p;

    for (int i = 0; i < 5; ++i)
    {
        polynomial *cursor = front;

        while (cursor != NULL)
        {
            if ((cursor->next != NULL) && (cursor->exp < cursor->next->exp))
            {
                int tempExp = cursor->exp;

                cursor->exp = cursor->next->exp;
                cursor->next->exp = tempExp;

                int tempCoeff = cursor->coeff;

                cursor->coeff = cursor->next->coeff;
                cursor->next->coeff = tempCoeff;
            }
            cursor = cursor->next;
        }
    }
}

double
poly_eval(
    polynomial * p,
    double x)
{
    //Substitues every x in the passed polynomial
    //for the supplied number, and finds the result.
    double sum = 0;

    while (p != NULL)
    {
        sum += pow(x, p->exp) * p->coeff;
        p = p->next;
    }
    return (sum);
}
