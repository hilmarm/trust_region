//
// Created by hilmarm on 13.07.16.
//

#ifndef TRUST_REGION_ALG_MODEL_H
#define TRUST_REGION_ALG_MODEL_H

#include <Eigen/Dense>
#include <QList>
#include "polynomial.h"

class Model {

private:
    // Member variabes
    QList<Eigen::VectorXd> points_;
    QList<double> fvalues_;
    Eigen::VectorXd center_;
    double radius_;
    QList<Polynomial> basis_;
    // Private methods/sub-methods
    Eigen::VectorXd find_new_point(Polynomial poly) const;


public:
    Model(QList<Eigen::VectorXd> points, QList<double> fvalues, double radius, QList<Polynomial> basis);
    QList<Eigen::VectorXd> get_points() const;
    QList<double> get_fvalues() const;
    double get_radius() const;
    QList<Polynomial> get_basis() const;

    /* Complete set of interpolation points
     * using Algorithm 5 as described in paper
     * by C. Giuliani
     */
    void complete_points();

};


#endif //TRUST_REGION_ALG_MODEL_H
