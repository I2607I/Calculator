#include "backcalc.h"

// int main() {
//     double res = 0;
//     //char input[256] = "(5+5)*2+log(100)";
//     //char input[256] = "12/6";
//     //char input[256] = "2*9";
//     //char input[256] = "2*9/ln(6)";
//     //char input[256] = "ln(6)";
//     char input[256] = "log(x)";
//     int e = main_func(input, &res, 5);
//     return 0;
// }

int pre_proces(char *input, char *output) {
    int i = 0;
    int j = 0;
    if (input[0] == '+' || input[0] == '-') {
        output[0] = '0';
        j++;
    }
    for (; i < strlen(input) - 1; i++) {
        if (input[i] == '(' && IsPlusMinus(input[i+1])) {
            output[j] = '(';
            j++;
            output[j] = '0';
            j++;
        } else {
            output[j] = input[i];
            j++;
        }
    }
    output[j] = input[i];
    return 0;
}

int proces(char* a, double*b, char* c, int *len_b, double value_x) {
    int er = 0;
    char tmp[256]={'+'};
    int i = 0;
    int j = 0;
    int dot = 0;
    int flag_dot = 0;
    int flag_correst_symb = 0;
    while (i < strlen(a)) {
        if (symbIsNumber(a[i]) == 0) {
            if (a[i] == '.') {
                dot = j;
                flag_dot = 1;
            }
            tmp[j] = a[i];
            j++;
            c[i] = '.';
        } else {
            if (tmp[0] != '+') {
                if (flag_dot == 0) {
                    dot = j;
                }
                b[*len_b] = str_to_float(tmp, j, dot);
                *len_b = *len_b +1;
            }
            if (a[i] == 'x') {
                b[*len_b] = value_x;
                *len_b = *len_b +1;
            }
            if (symbIsOperator(a[i]) == 0) {
                c[i] = a[i];
            } else if (a[i] == '(' || a[i] == ')' || a[i] == 'x') {
                c[i] = a[i];
            } else if (i+3 <= strlen(a)) {
                if (a[i] == 'l' && a[i+1] == 'n') {
                    c[i] = c[i+1] = c[i+2] = 'l';
                    i+=1;
                } else if (i+4 <= strlen(a)) {
                if (a[i] == 's' && a[i+1] == 'i' && a[i+2] == 'n') {
                    c[i] = c[i+1] = c[i+2] = 's';
                    i+=2;
                } else if (a[i] == 'c' && a[i+1] == 'o' && a[i+2] == 's') {
                    c[i] = c[i+1] = c[i+2] = 'c';
                    i+=2;
                } else if (a[i] == 't' && a[i+1] == 'a' && a[i+2] == 'n') {
                    c[i] = c[i+1] = c[i+2] = 't';
                    i+=2;
                } else if (a[i] == 'l' && a[i+1] == 'o' && a[i+2] == 'g') {
                    c[i] = c[i+1] = c[i+2] = 'd';
                    i+=2;
                } else if (a[i] == 'm' && a[i+1] == 'o' && a[i+2] == 'd') {
                    c[i] = c[i+1] = c[i+2] = '%';
                    i+=2;
                } else if (i+5 <= strlen(a)) {
                    if (a[i] == 'a' && a[i+1] == 'c' && a[i+2] == 'o' && a[i+3] == 's') {
                        c[i] = c[i+1] = c[i+2] = c[i+3] = 'o';
                        i+=3;
                    } else if (a[i] == 'a' && a[i+1] == 's' && a[i+2] == 'i' && a[i+3] == 'n') {
                        c[i] = c[i+1] = c[i+2] = c[i+3] = 'i';
                        i+=3;
                    } else if (a[i] == 'a' && a[i+1] == 't' && a[i+2] == 'a' && a[i+3] == 'n') {
                        c[i] = c[i+1] = c[i+2] = c[i+3] = 'a';
                        i+=3;
                    } else if (a[i] == 's' && a[i+1] == 'q' && a[i+2] == 'r' && a[i+3] == 't') {
                        c[i] = c[i+1] = c[i+2] = c[i+3] = 'q';
                        i+=3;
                    } else {
                        er = 1;
                    }
                }
            }
            } else {
                c[i] = 'w';
                er = 1;
                break;
            }
            for (int h = 0; h < 256; h++) {
                tmp[h] = '+';
            }
            j = 0;
            dot = 0;
            flag_dot = 0;
        }
        i++;
    }
    if (tmp[0] != '+') {
        if (flag_dot == 0) {
            dot = j;
        }
        b[*len_b] = str_to_float(tmp, j, dot);
        *len_b = *len_b +1;
    }
    return er;
}

int symbIsNumber(char s) {
    int res = 1;
    char str[12] = "0123456789.";
    for (int i = 0; i < strlen(str); i++) {
        if (s == str[i]) {
            res = 0;
        }
    }
    return res;
}

int symbIsOperator(char s) {
    int res = 1;
    char str[7] = "-+*/^%%";
    for (int i = 0; i < 6; i++) {
        if (s == str[i]) {
            res = 0;
        }
    }
    return res;
}

int symbIsFunction(char s) {
    int res = 1;
    char str[11] = "lsctdoiaqqa";
    for (int i = 0; i < strlen(str); i++) {
        if (s == str[i]) {
            res = 0;
        }
    }
    return res;
}

int pr(char t) {
    char str[7] = "-+*/^%%";
    int priority[6] = {1, 1, 2, 2, 3, 2};
    int i = 0;
    int flag = 0;
    for (; i < 6; i++) {
        if (t == str[i]) {
            flag = 1;
            break;
        }
    }
    return priority[i]*flag;
}

int shunting_yard(char *input, char *output) {
    Stack_t stack;
    stack.size = 0;
    int i = 0;
    int j = 0;
    char mycor = '1';
    for (; i < strlen(input); ++i) {
        char t = input[i];
        if (t == '.' || t == 'x') {
            output[j] = '.';
            j++;
        }

        if (symbIsFunction(t) == 0) {
            push(&stack, t);
        }
        if (symbIsOperator(t) == 0) {
            if (stack.size >= 1) {
                while (symbIsOperator(peek(&stack) == 0) && pr(peek(&stack)) >= pr(t)) {
                    output[j] = pop(&stack);
                    j++;
                    if (stack.size == 0 || peek(&stack) == '(') {
                        break;
                    }
                }
            }
            push(&stack, t);
        }
        if (t == '(') {
            push(&stack, t);
        }
        if (t == ')') {
            while (peek(&stack) != '(') {
                    output[j] = pop(&stack);
                    j++;
            }
            mycor = pop(&stack);
            if (stack.size >= 1) {
                if (symbIsFunction(peek(&stack)) == 0) {
                    output[j] = pop(&stack);
                    j++;
                }
            }
        }
    }
    int oct_size = stack.size;
    for (int i = 0; i < oct_size; i++) {
        output[j] = pop(&stack);
        j++;
    }
    return 0;
}

double calc(char* input, double* number) {
    Stack_t2 new_stack;
    new_stack.size = 0;
    int j = 0;
    for (int i = 0; i < strlen(input); ++i) {
        char t = input[i];
        if (symbIsOperator(t) == 0) {
            double y = pop2(&new_stack);
            double x = pop2(&new_stack);
            if (t == '-') {
                push2(&new_stack, x-y);
            }
            if (t == '+') {
                push2(&new_stack, x+y);
            }
            if (t == '*') {
                push2(&new_stack, x*y);
            }
            if (t == '/') {
                push2(&new_stack, x/y);
            }
            if (t == '^') {
                push2(&new_stack, pow(x, y));
            }
            if (t == '%') {
                push2(&new_stack, fmod(x, y));
            }
        } else if (symbIsFunction(t) == 0) {
            double z = pop2(&new_stack);
            if (t == 's') {
                push2(&new_stack, sin(z));
            } else if (t == 'c') {
                push2(&new_stack, cos(z));
            } else if (t == 't') {
                push2(&new_stack, tan(z));
            } else if (t == 'd') {
                push2(&new_stack, log10(z));
            } else if (t == 'l') {
                push2(&new_stack, log(z));
            } else if (t == 'o') {
                push2(&new_stack, acos(z));
            } else if (t == 'i') {
                push2(&new_stack, asin(z));
            } else if (t == 'a') {
                push2(&new_stack, atan(z));
            } else if (t == 'q') {
                push2(&new_stack, sqrt(z));
            }
        } else {
            push2(&new_stack, number[j]);
            j++;
        }
    }
    return pop2(&new_stack);
}

int index_symbol(char s) {
    char symbol_priority[4] = {'+', '-', '*', '/'};
    int i = 0;
    for (; i < strlen(symbol_priority); i++) {
        if (s == symbol_priority[i]) {
            break;
        }
    }
    return i;
}

double str_to_float(char *a, int lenn, int dot) {
    double res = 0;
    for (int i = dot - 1; i >= 0; i--) {
        int x = a[i] - '0';
        res+=x*pow(10, dot - i - 1);
    }
    for (int j = dot +1; j < lenn; j++) {
        int x = a[j] - '0';
        res += x*pow(10, -(j-dot));
    }
    return res;
}

int post_proces(char *c, char *d) {
    int n = strlen(c);
    int i = 0;
    int j = 0;
    while (i < n - 1) {
        if (c[i] == '(' || c[i] == ')') {
            d[j] = c[i];
            j++;
        } else if (c[i] != c[i+1]) {
            d[j] = c[i];
            j++;
        }
        i++;
    }
    if (c[n - 1] != d[j-1]) {
        d[j] = c[n-1];
    }
    if (c[n-1] == d[j-1] && c[n-1] == ')') {
        d[j] = c[n-1];
    }
    return strlen(d);
}

void push(Stack_t *stack, const char value) {
    if (stack->size >= STACK_MAX_SIZE) {
        exit(STACK_OVERFLOW);
    }
    stack->data[stack->size] = value;
    stack->size++;
}


char pop(Stack_t *stack) {
    if (stack->size == 0) {
        exit(STACK_UNDERFLOW);
    }
    stack->size--;
    return stack->data[stack->size];
}


char peek(const Stack_t *stack) {
    if (stack->size <= 0) {
        exit(STACK_UNDERFLOW);
    }
    return stack->data[stack->size - 1];
}

void push2(Stack_t2 *stack, const double value) {
    if (stack->size >= STACK_MAX_SIZE) {
        exit(STACK_OVERFLOW);
    }
    stack->data[stack->size] = value;
    stack->size++;
}


double pop2(Stack_t2 *stack) {
    if (stack->size == 0) {
        exit(STACK_UNDERFLOW);
    }
    stack->size--;
    return stack->data[stack->size];
}


double peek2(const Stack_t2 *stack) {
    if (stack->size <= 0) {
        exit(STACK_UNDERFLOW);
    }
    return stack->data[stack->size - 1];
}

int IsPlusMinus(char a) {
    int flag = 0;
    if (a == '+' || a == '-') {
        flag = 1;
    }
    return flag;
}

int main_func(char *input, double* output_res, double value_x) {
    char res_pre_proces[512] = "";
    char output[512] = "";
    double number[512] = {nan("")};
    char d[512] = "";
    char res[512] = "";
    int g = pre_proces(input, res_pre_proces);            // исправляет унарные операции
    int dottt = check_two_dot(input);
    int kkk = 0;
    int e = proces(res_pre_proces, number, output, &kkk, value_x);  // числа переводит в отдельный массив
    if (!e) {
        int count_token = post_proces(output, d);  // удаляет повторяющие символы
        int s = shunting_yard(d, res);  // сортировочная сатнция
        *output_res = calc(res, number);  // вычисление выражения в польской нотации обратной
    }
    return (e || dottt);
}

int check_two_dot(char *a) {
    int res = 0;
    int flag_dot = 0;
    int flag_plus = 0;
    for (int i = 0; i < strlen(a); i++) {
        if (a[i] == '.') {
            if (flag_dot) {
                res = 1;
                break;
            }
            flag_dot = 1;
        } else {
            flag_dot = 0;
        }
        if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/' || a[i] == '^') {
            if (flag_plus) {
                res = 1;
                break;
            }
            flag_plus = 1;
        } else {
            flag_plus = 0;
        }
    }
    return res;
}

double s21_calc_credit(double sum_number, double term_number,
 double procent_number, double*over, double *pay) {
    double pc = procent_number/12/100;
    double res = sum_number*pc/(1-pow(1+pc, term_number*(-1)));
    *over = res*term_number - sum_number;
    *pay = *over + sum_number;
    return res;
}

int isx(char *a) {
    int res = 0;
    for (int i = 0; i < strlen(a); i++) {
        if (a[i] == 'x') {
            res = 1;
            break;
        }
    }
    return res;
}


