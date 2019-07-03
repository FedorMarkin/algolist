#ifndef BINARY_SEARCH_HPP
#define BINARY_SEARCH_HPP

#include <cmath>

int binary_search_array (int *arr, int n, int val) { // return an index of the first element equal or greater than val
    int L = -1, R = n, m;
    while (L + 1 < R) {
        m = L + (R-L)/2;
        if (arr[m] > val) R = m;
        else L = m;
    }
    return R;
}

#endif // BINARY_SEARCH_HPP
