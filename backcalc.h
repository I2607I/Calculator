#ifndef SRC_BACKCALC_H_
#define SRC_BACKCALC_H_
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define STACK_MAX_SIZE 512
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101


typedef struct Stack_tag {
    char data[STACK_MAX_SIZE];
    int size;
} Stack_t;

typedef struct Stack_tag2 {
    double data[STACK_MAX_SIZE];
    int size;
} Stack_t2;

int pre_proces(char *input, char *output);
int proces(char* a, double*b, char* c, int *len_b, double value_x);
int symbIsNumber(char s);
int symbIsOperator(char s);
int shunting_yard(char *input, char *output);
int index_symbol(char s);
double str_to_float(char *a, int lenn, int dot);
int post_proces(char *c, char *d);
int pr(char t);
void push(Stack_t *stack, const char value);
char pop(Stack_t *stack);
char peek(const Stack_t *stack);
void push2(Stack_t2 *stack, const double value);
double pop2(Stack_t2 *stack);
double peek2(const Stack_t2 *stack);
double calc(char* input, double *number);
int IsPlusMinus(char a);
int main_func(char *input, double* output_res, double value_x);
int check_two_dot(char *a);
double s21_calc_credit(double sum_number, double term_number,
    double procent_number, double*over, double *pay);
int isx(char *a);

#endif  // SRC_BACKCALC_H_
