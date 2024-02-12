//
// Created by angus on 12/02/2024.
//


#include "config.h"

mpz_class min(const mpz_class& a, const mpz_class& b) {
    return a <= b ? a : b;
}

mpz_class max(const mpz_class& a, const mpz_class& b) {
    return a >= b ? a : b;
}
