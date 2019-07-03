#ifndef SEGMENT_TREE_HPP
#define SEGMENT_TREE_HPP

#include <iostream>
#include <vector>

/*
* tree node
*/

struct node {
    int sum;
    node *left = nullptr;
    node *right = nullptr;
};


class Segment_tree {
    int n;
    node *T;
    std::vector<int> *vc;
    std::vector<node*> stk;
    /*
    * builds segment tree from an array
    */
    void build_tree(node *&p, int L, int R) {
        if (L == R) {
            p = new node;
            p->sum = vc->at(L);
            //std::cout << p->sum << std::endl;
        } else {
            p = new node;
            int m = L + (R-L)/2;
            build_tree(p->left, L, m);
            build_tree(p->right, m+1, R);
            p->sum = p->left->sum + p->right->sum;
        }
    }
    /*
    * prints tree
    */
    void print_tree(node *p, int ind) {
        if (p == nullptr) return;
        for (int i = 0; i < ind; ++i) std::cout << "  ";
        std::cout << p->sum << std::endl;
        print_tree(p->left, ind+1);
        print_tree(p->right, ind+1);
    }
    /*
    * returns sum of elements of a specific segment in array
    */
    int get_sum(node *p, int tl, int tr, int L, int R) {
        if (L > R || p == nullptr) return 0;
        if (tl == L && tr == R) return p->sum;
        int m = tl + (tr-tl)/2;
        return get_sum(p->left, tl, m, L, std::min(R, m)) + get_sum(p->right, m+1, tr, std::max(L, m+1), R);
    }
    /*
    * clears memory, used in destructor
    */
    void delete_tree(node *T) {
        if (T == nullptr) return;
        delete_tree(T->left);
        delete_tree(T->right);
        delete T;
    }
    /*
    * changes tree but not array
    * updates tree after changing ones element
    */
    void upd_tree(int tl, int tr, int pos, int new_val) {
        node *p = T;
        int tm;
        stk.resize(0);
        while (tl != tr && p != nullptr) {
            stk.push_back(p);
            tm = tl+(tr-tl)/2;
            if (pos <= tm) tr = tm, p = p->left;
            else tl = tm+1, p = p->right;
        }
        if (p != nullptr) p->sum = new_val;
        while (!stk.empty()) {
            p = stk.back();
            stk.pop_back();
            if (p->left || p->right) {
                p->sum = 0;
                if (p->left != nullptr) p->sum += p->left->sum;
                if (p->right != nullptr) p->sum += p->right->sum;
            }
        }
        stk.clear();
    }
public:
    Segment_tree(std::vector<int> &arr) {
        vc = &arr;
        n = arr.size();
        build_tree(T, 0, arr.size()-1);
    }
    ~Segment_tree() {
        delete_tree(T);
    }
    /*
    * Safe functions
    */
    void print() {
        print_tree(T, 0);
    }
    int sum(int L, int R) {
        if (L < 0) L = 0;
        if (R >= n) R = n-1;
        return get_sum(T, 0, n-1, L, R);
    }
    void update(int pos, int new_val) {
        if (pos < 0 || pos >= n) return;
        upd_tree(0, n-1, pos, new_val);
    }
};

#endif // SEGMENT_TREE_HPP
