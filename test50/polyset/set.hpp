#pragma once

#include "searchable_bag.hpp"

class set {
private:
    searchable_bag *bag;
    bool owns_bag;

public:
    set(searchable_bag &bag_ref);
    set(const set &src);
    set &operator=(const set &src);
    ~set();
    
    void insert(int item);
    void insert(int *items, int count);
    bool has(int item) const;
    void print() const;
    void clear();
    searchable_bag &get_bag() const;
};