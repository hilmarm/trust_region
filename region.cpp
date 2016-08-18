//
// Created by hilmarm on 30.06.16.
//

#include "region.h"

 region::region(int index) {
     index_ = index;
 }

int region::return_index() {
    return index_;
}

double region::obj_f_(double i, double j) {
    return 3;
}

double region::eval_f(double i, double j) {
    return obj_f_(i,j);
}
