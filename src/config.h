//
// Created by angus on 10/02/2024.
//

#ifndef SRC_CONFIG_H
#define SRC_CONFIG_H

#include <gmpxx.h>

//typedef mpz_class int_t;
typedef long long int_t;
//typedef mpq_class f_t;
typedef double f_t;

mpz_class min(const mpz_class& a, const mpz_class& b);
mpz_class max(const mpz_class& a, const mpz_class& b);

//int_t min(int_t &a, int_t &b) {
//    if(a <= b) return a;
//    return b;
//}

#endif //SRC_CONFIG_H
