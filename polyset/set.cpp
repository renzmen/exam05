#include "set.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include <typeinfo>


set::set(searchable_bag &bag_ref) : bag(&bag_ref), owns_bag(false) {
}


set::set(const set &src) : owns_bag(true) {
    // Determina il tipo dell'oggetto puntato da src.bag
    searchable_array_bag *array_bag_ptr = dynamic_cast<searchable_array_bag*>(src.bag);

    searchable_tree_bag *tree_bag_ptr = dynamic_cast<searchable_tree_bag*>(src.bag);
    
    if (array_bag_ptr) {
        bag = new searchable_array_bag(*array_bag_ptr);
    } else if (tree_bag_ptr) {
        bag = new searchable_tree_bag(*tree_bag_ptr);
    } else {
        // Fallback - crea un array bag vuoto
        bag = new searchable_array_bag();
    }
}


set &set::operator=(const set &src) {
    if (this != &src) {
        if (owns_bag && bag) {
            delete bag;
        }
        
        owns_bag = true;
        
        // Determina il tipo dell'oggetto puntato da src.bag
        searchable_array_bag *array_bag_ptr = dynamic_cast<searchable_array_bag*>(src.bag);
        searchable_tree_bag *tree_bag_ptr = dynamic_cast<searchable_tree_bag*>(src.bag);
        
        if (array_bag_ptr) {
            bag = new searchable_array_bag(*array_bag_ptr);
        } else if (tree_bag_ptr) {
            bag = new searchable_tree_bag(*tree_bag_ptr);
        } else {
            // Fallback - crea un array bag vuoto
            bag = new searchable_array_bag();
        }
    }
    return *this;
}


set::~set() {
    if (owns_bag && bag) {
        delete bag;
    }
}


void set::insert(int item) {
    if (!bag->has(item)) {
        bag->insert(item);
    }
}


void set::insert(int *items, int count) {
    for (int i = 0; i < count; i++) {
        insert(items[i]);
    }
}


bool set::has(int item) const {
    return bag->has(item);
}


void set::print() const {
    bag->print();
}


void set::clear() {
    bag->clear();
}


searchable_bag &set::get_bag() const {
    return *bag;
}