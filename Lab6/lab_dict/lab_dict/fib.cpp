/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <map>

using std::map;

/** 
 * Calculates the nth Fibonacci number where the zeroth is defined to be 
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    if (n == 0) {
    return 0;
    } else if (n == 1) {
        return 1;
    }

    return fib(n-1) + fib(n-2);
}

/** 
 * Calculates the nth Fibonacci number where the zeroth is defined to be 
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{

    static map< unsigned long, unsigned long > fib_map =
    {
        {0, 0},
        {1, 1}
    };
    unsigned long fib_num;
    
    if (n == 0) {
    return 0;
    } else if (n == 1) {
        return 1;
    }
    auto it = fib_map.find(n-1);

    if (it != fib_map.end()) {
        fib_num = fib_map[n-1] + fib_map[n-2];
    } else {
        fib_num = memoized_fib(n-1);
    }

    fib_map[n] = fib_num;

    return fib_map[n];
}
