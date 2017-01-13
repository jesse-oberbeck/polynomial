#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct term {
    int coeff;
    unsigned int exp;
    struct term *next;
};
typedef struct term polynomial;



struct term *term_create(int coeff, int exp)
{
    struct term *node = malloc(sizeof(*node));
    if(node)
    {
        node->coeff = coeff;
        node->exp = exp;
        node->next = NULL;
    }
    return node;
}

void poly_destroy(polynomial *eqn)
{
    while(eqn)
    {
        struct term *tmp = eqn->next;
        free(eqn);
        eqn = tmp;
    }
}

void poly_print(const polynomial *eqn)
{
    if(!eqn)
    {
        return;
    }
    if(eqn->coeff)
    {
        printf("%c%d", eqn->coeff > 0 ? '+' : '\0', eqn->coeff);
        if(eqn->exp > 1)
        {
            printf("x^%d", eqn->exp);
        }
        else if(eqn->exp == 1)
        {
            printf("x");
        }
        printf(" ");
    }
    poly_print(eqn->next);
}
///////////////////////////////////////////////
polynomial *poly_add(const polynomial *a, const polynomial *b)
{

    polynomial *sum = calloc(sizeof(polynomial), 1);
    polynomial *cursor = sum;
    while(a && b)
    {
        //printf("ac : %d\n", a->coeff);
        if(a->exp == b->exp)
        {
            puts("equal");
            cursor->exp = a->exp;
            cursor->coeff = (a->coeff + b->coeff);
            a = a->next;
            b = b->next;
            cursor->next = calloc(sizeof(polynomial), 1);
            cursor = cursor->next;
        }
        else if(a->exp > b->exp)
        {
            puts("a");
            cursor->exp = a->exp;
            cursor->coeff = a->coeff;
            if(a->next != NULL)
            {
                a = a->next;
            }
            cursor->next = calloc(sizeof(polynomial), 1);
            cursor = cursor->next;
        }
        else if(a->exp < b->exp)
        {
            puts("b");
            cursor->exp = b->exp;
            cursor->coeff = b->coeff;
            if(b->next != NULL)
            {
                b = b->next;
            }
            cursor->next = calloc(sizeof(polynomial), 1);
            cursor = cursor->next;
        }

    }
    //printf("sum c: %d\n", sum->coeff);
        return(sum);
}

//WRITE A SIMPLIFY FUNCTION


/*
char *poly_to_string(const polynomial *p)
{
    char string[42];
    snprintf(string, 42, "%s", poly_print(p));
    return(string);
}
*/

///////////////////////////////////////////////
int main(void)
{
    polynomial *first = term_create(3, 3);
    polynomial *second = term_create(5, 1);
    polynomial *third = term_create(1, 0);

    first->next = second;
    second->next = third;

    polynomial *a = term_create(7, 2);
    polynomial *b = term_create(-5, 1);
    polynomial *c = term_create(3, 0);

    a->next = b;
    b->next = c;

    polynomial *sum = poly_add(first, a);
    poly_print(sum);
    //char *result = (poly_to_string(first));
    puts("");
}
