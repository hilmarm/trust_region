//
// Created by hilmarm on 15.07.16.
//

#ifndef TRUST_REGION_ALG_POLYNOMIAL_H
#define TRUST_REGION_ALG_POLYNOMIAL_H


#include <Eigen/Core>
#include <iostream>

class Polynomial {
private:
    int dimension_;
    int no_elemts_;
    Eigen::VectorXd coeffs_;

public:
    Polynomial(int dimension, Eigen::VectorXd coeffs);
    Eigen::VectorXd return_coeffs() const;
    int return_dimension() const;
    int return_no_elements() const;
    double evaluate(Eigen::VectorXd point) const;
    Eigen::VectorXd evaluateGradient(Eigen::VectorXd point);
    void add(Polynomial poly);
    void multiply(double k);

};


#endif //TRUST_REGION_ALG_POLYNOMIAL_H
