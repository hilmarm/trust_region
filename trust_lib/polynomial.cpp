//
// Created by hilmarm on 15.07.16.
//

#include "polynomial.h"
#include <iostream>

Polynomial::Polynomial(int dimension, Eigen::VectorXd coeffs) {
    dimension_ = dimension;
    coeffs_ = coeffs;
    no_elemts_ = (dimension+1)*(dimension+2)/2;
}

void Polynomial::add(Polynomial poly) {

    if(poly.return_no_elements()!= no_elemts_){
        std::cout << "polynomials have different dimensions" << std::endl;
    }

    else{
        for(int i=0; i<no_elemts_; i++){
            coeffs_(i) = coeffs_(i) + poly.coeffs_(i);
        }
    }

}

void Polynomial::multiply(double k) {
    coeffs_ = k*coeffs_;

}

double Polynomial::evaluate(Eigen::VectorXd point) const{

    /* Assume quadratic monomial basis as presented
     * in Caio Giuliani's summary, but with a slight
     * change in ordering. Here the constant term is
     * the first one, then the linear terms, then
     * the quadratic terms of one variable, and finally
     * the mixed terms. i.e. (1, x_1, x_2,..., 0.5*x_N,
     * 0.5*x_1^2, x_2^2,..., 0.5*x_N^2, x_1*x_2, x_1*x_3,
     * ..., x_(N-1)*x_N )
     */

    // CHECK POLYNOMIAL AND POINT DIMENSIONS SAME
    double sum = coeffs_(0);
    for(int i=0; i<dimension_; i++){
        // Linear term and quadratic single term
        sum = sum + coeffs_(i+1)*point(i);
        sum = sum + 0.5*coeffs_(dimension_+i+1)*point(i)*point(i);
    }

    // iter is just an iterator to keep track of where we are in the
    // coefficient vector. Simpler than writing as a function of i and j
    int iter = 2*dimension_+1;

    for(int i=0; i<dimension_-1; i++){
        for(int j=i+1; j<dimension_; j++){
            sum = sum + coeffs_(iter)*point(i)*point(j);
            iter = iter +1;
        }
    }

    return sum;
}

int Polynomial::return_no_elements() const{
    return no_elemts_;
}

int Polynomial::return_dimension() const{
    return dimension_;
}

Eigen::VectorXd Polynomial::return_coeffs() const{
    return coeffs_;
}
