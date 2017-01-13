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
polynomial * simplify(const polynomial *p)
{
    polynomial *front = p;
    polynomial *cursor;
    cursor = p;
    while(cursor->next != NULL)
    {
        if(cursor->exp == cursor->next->exp)
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
    return(front);
}


polynomial *poly_add(const polynomial *a, const polynomial *b)
{

    polynomial *sum = calloc(sizeof(polynomial), 1);
    polynomial *cursor = sum;
    while(a && b)
    {
        //printf("ac : %d\n", a->coeff);
        if(a->exp == b->exp)
        {
            //puts("equal");
            cursor->exp = a->exp;
            cursor->coeff = (a->coeff + b->coeff);
            a = a->next;
            b = b->next;
        }
        else if(a->exp > b->exp)
        {
            //puts("a");
            cursor->exp = a->exp;
            cursor->coeff = a->coeff;
            a = a->next;
        }
        else if(a->exp < b->exp)
        {
            //puts("b");
            cursor->exp = b->exp;
            cursor->coeff = b->coeff;
            b = b->next;
        }
        cursor->next = calloc(sizeof(polynomial), 1);
        cursor = cursor->next;
    }
    //printf("sum c: %d\n", sum->coeff);
        return(sum);
}


polynomial *poly_sub(const polynomial *a, const polynomial *b)
{
    simplify(a);
    simplify(b);
    polynomial *sum = calloc(sizeof(polynomial), 1);
    polynomial *cursor = sum;
    while(a && b)
    {
        //printf("ac : %d\n", a->coeff);
        if(a->exp == b->exp)
        {
            //puts("equal");
            cursor->exp = a->exp;
            cursor->coeff = (a->coeff - b->coeff);
            a = a->next;
            b = b->next;
        }
        else if(a->exp > b->exp)
        {
            //puts("a");
            cursor->exp = a->exp;
            cursor->coeff = a->coeff;
            a = a->next;
        }
        else if(a->exp < b->exp)
        {
            //puts("b");
            cursor->exp = b->exp;
            cursor->coeff = b->coeff;
            b = b->next;
        }
        cursor->next = calloc(sizeof(polynomial), 1);
        cursor = cursor->next;
    }
    //printf("sum c: %d\n", sum->coeff);
        return(sum);
}


char *poly_to_string(const polynomial *p)
{
    const polynomial *cursor = p;
    char *buffer = calloc(42 , 1);

    while(cursor != NULL)
    {
        if(!cursor)
        {
            sprintf(buffer, "Nothing");
            return(buffer);
        }
        if(cursor->coeff)
        {
            sprintf(buffer,"%s%c%d", buffer, cursor->coeff > 0 ? '+' : '\0', cursor->coeff);
            if(cursor->exp > 1)
            {
                sprintf(buffer, "%sx^%d ", buffer, cursor->exp);
            }
            else if(cursor->exp == 1)
            {
                sprintf(buffer, "%sx ", buffer);
            }
            printf(" ");
        }
        cursor = cursor->next;
    }
    return(buffer);
}


///////////////////////////////////////////////
int main(void)
{
    polynomial *first = term_create(3, 3);
    polynomial *second = term_create(5, 1);
    polynomial *third = term_create(1, 0);

    first->next = second;
    second->next = third;

    polynomial *a = term_create(7, 2);
    polynomial *b = term_create(3, 2);
    polynomial *c = term_create(5, 0);
    polynomial *d = term_create(4, 0);
    polynomial *e = term_create(3, 0);

    a->next = b;
    b->next = c;
    c->next = d;
    d->next = e;
    //simplify(&a);
    polynomial *sum = poly_sub(first, a);
    poly_print(sum);
    puts("");
    //simplify(&a);
    poly_print(a);
    char *result = (poly_to_string(first));
    printf("\nresult: %s\n", result);
    puts("");
}
