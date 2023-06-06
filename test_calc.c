#include <check.h>
#include "backcalc.h"

int eq_number(double a, double b);

START_TEST(test1) {
    double res = 0;
//  char input[256] = "(5+5)*2+log(100)";
//  char input[256] = "12/6";
//  char input[256] = "2*9";
//  char input[256] = "2*9/ln(6)";
//  char input[256] = "ln(6)";
//  char input[256] = "log(x)";
    char input[256] = "5+5";
    int e = main_func(input, &res, 0);
    int i =  eq_number(res, 10);
    ck_assert_msg(i, "FAIL");
}
END_TEST

START_TEST(test2) {
    double res = 0;
//  char input[256] = "(5+5)*2+log(100)";
//  char input[256] = "2*9";
//  char input[256] = "2*9/ln(6)";
//  char input[256] = "ln(6)";
//  char input[256] = "log(x)";
    char input[256] = "12/6";;
    int e = main_func(input, &res, 0);
    int i =  eq_number(res, 2);
    ck_assert_msg(i, "FAIL");
}
END_TEST

START_TEST(test3) {
    double res = 0;
//  char input[256] = "(5+5)*2+log(100)";
//  char input[256] = "2*9";
//  char input[256] = "2*9/ln(6)";
//  char input[256] = "log(x)";
    char input[256] = "ln(6)";
    int e = main_func(input, &res, 0);
    int i =  eq_number(res, 1.79175947);
    ck_assert_msg(i, "FAIL");
}
END_TEST

START_TEST(test4) {
    double res = 0;
//  char input[256] = "(5+5)*2+log(100)";
//  char input[256] = "2*9";
//  char input[256] = "2*9/ln(6)";
//  char input[256] = "log(x)";
    char input[256] = "cos((6*21)*sin(tan(5+2)))";
    int e = main_func(input, &res, 0);
    int i =  eq_number(res, -0.568280848);
    ck_assert_msg(i, "FAIL");
}
END_TEST

START_TEST(test5) {
    double res = 0;
    char input[256] = "-5";
    int e = main_func(input, &res, 0);
    int i =  eq_number(res, -5);
    ck_assert_msg(i, "FAIL");
}
END_TEST

START_TEST(test6) {
    double res = 0;
    char input[256] = "(-5)*12.5";
    int e = main_func(input, &res, 0);
    int i =  eq_number(res, -62.5);
    ck_assert_msg(i, "FAIL");
}
END_TEST

START_TEST(test7) {
    double res = 0;
    char input[256] = "log(100)+sqrt(4)+asin(0)+acos(1)+atan(0)";
    int e = main_func(input, &res, 0);
    int i =  eq_number(res, 4);
    ck_assert_msg(i, "FAIL");
}
END_TEST

START_TEST(test8) {
    double res = 0;
    char input[256] = "acor(3)";
    int e = main_func(input, &res, 0);
    //int i =  eq_number(res, 4);
    ck_assert_msg(e, "FAIL");
}
END_TEST

START_TEST(test9) {
    double res = 0;
    char input[256] = "a";
    int e = main_func(input, &res, 0);
    //int i =  eq_number(res, 4);
    ck_assert_msg(e, "FAIL");
}
END_TEST

START_TEST(test10) {
    double res = 0;
    char input[256] = "5mod2+2^3";
    int e = main_func(input, &res, 0);
    int i =  eq_number(res, 9);
    ck_assert_msg(i, "FAIL");
}
END_TEST

START_TEST(test11) {
    double res = 0;
    char input[256] = "4..4+2";
    int e = main_func(input, &res, 0);
    //int i =  eq_number(res, 4);
    ck_assert_msg(e, "FAIL");
}
END_TEST

START_TEST(test12) {
    double res = 0;
    char input[256] = "4+3*4/2+3*5^2";
    int e = main_func(input, &res, 0);
    int i =  eq_number(res, 85);
    ck_assert_msg(i, "FAIL");
}
END_TEST

START_TEST(test13) {
    double res = 0;
    char input[256] = "5";
    int e = main_func(input, &res, 0);
    int i =  eq_number(res, 5);
    ck_assert_msg(i, "FAIL");
}
END_TEST

START_TEST(test14) {
    double res = 0;
    char input[256] = "(((((((((((5)))))))))))";
    int e = main_func(input, &res, 0);
    int i =  eq_number(res, 5);
    ck_assert_msg(i, "FAIL");
}
END_TEST

Suite *s21_string_suite(void) {
    Suite *suite;
    TCase *getCase;

    suite = suite_create("String");
    getCase = tcase_create("core");

    tcase_add_test(getCase, test1);
    tcase_add_test(getCase, test2);
    tcase_add_test(getCase, test3);
    tcase_add_test(getCase, test4);
    tcase_add_test(getCase, test5);
    tcase_add_test(getCase, test6);
    tcase_add_test(getCase, test7);
    tcase_add_test(getCase, test8);
    tcase_add_test(getCase, test9);
    tcase_add_test(getCase, test10);
    tcase_add_test(getCase, test11);
    tcase_add_test(getCase, test12);
    tcase_add_test(getCase, test13);
    tcase_add_test(getCase, test14);
    suite_add_tcase(suite, getCase);

    return suite;
}

int main(void) {
    int amountOfFailed = 0;
    Suite *suite;
    SRunner *runner;

    suite = s21_string_suite();
    runner = srunner_create(suite);

    srunner_run_all(runner, CK_NORMAL);
    amountOfFailed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (amountOfFailed == 0) ? 0 : 1;
}

int eq_number(double a, double b) {
    int returnable = 0;
    double E = 0.0000001;
    if (fabs(a - b) < E)
        returnable = 1;
    return returnable;
}

