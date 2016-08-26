#include <iostream>
#include "region.h"
#include "trust_lib/model.h"
#include "trust_lib/polynomial.h"
#include <Eigen/Dense>
#include <QList>

using namespace std;

int main() {
    cout << "create polynomial" << endl;

    Eigen::VectorXd coeffs(6);
    int dim = 2;
    coeffs << 0, 0, 0, 1,1,1;
    Polynomial poly1 = Polynomial(dim, coeffs);

    Eigen::VectorXd point1(2), point2(2);
    point1 << 3,-3;
    point2 << 5, 0;
    std::cout << "P(3,-3) = " << poly1.evaluate(point1) << std::endl;
    std::cout << "P(5,0) = " << poly1.evaluate(point2) << std::endl;

    Eigen::VectorXd coeffs2(10);
    int dim2 = 3;
    coeffs2 << 0,1,0,0,0,1,0,0,1,0;
    Polynomial poly2 = Polynomial(dim2, coeffs2);

    Eigen::VectorXd point3(3);
    point3 << 1,-2, 120;
    std::cout << "P(1,-2,120) = " << poly2.evaluate(point3) << std::endl;

    Eigen::VectorXd point_0(2), point_1(2), point_2(2), point_3(2), point_4(2), point_5(2);
    point_0 << 0, 0;
    point_1 << 1, -1;
    point_2 << 1, 1;
    point_3 << 1, 1.01;
    point_4 << 1, 1;
    point_5 << 0, 0.2;

    QList<Eigen::VectorXd> points;
    points.append(point_0);
    points.append(point_1);
    points.append(point_2);
    points.append(point_3);
    points.append(point_4);
    points.append(point_5);
    QList<double> fvalues;
    fvalues.append(0);
    fvalues.append(1);
    fvalues.append(4);
    fvalues.append(-3);
    fvalues.append(2);
    fvalues.append(9);



    QList<Polynomial> basis;
    Eigen::VectorXd pol_0(6), pol_1(6), pol_2(6), pol_3(6), pol_4(6), pol_5(6);
    pol_0 << 1,0,0,0,0,0;
    pol_1 << 0,1,0,0,0,0;
    pol_2 << 0,0,1,0,0,0;
    pol_3 << 0,0,0,1,0,0;
    pol_4 << 0,0,0,0,1,0;
    pol_5 << 0,0,0,0,0,1;

    basis.append(Polynomial(2,pol_0));
    basis.append(Polynomial(2,pol_1));
    basis.append(Polynomial(2,pol_2));
    basis.append(Polynomial(2,pol_3));
    basis.append(Polynomial(2,pol_4));
    basis.append(Polynomial(2,pol_5));
    Polynomial poly_0 = Polynomial(2,pol_0);
    Polynomial poly_1 = Polynomial(2,pol_1);
    Polynomial poly_2 = Polynomial(2,pol_2);
    Polynomial poly_3 = Polynomial(2,pol_3);
    Polynomial poly_4 = Polynomial(2,pol_4);
    Polynomial poly_5 = Polynomial(2,pol_5);


    std::cout << "should be 1 = " << poly_0.evaluate(point_1) << std::endl;
    std::cout << "should be 1 = " << poly_1.evaluate(point_1) << std::endl;
    std::cout << "should be -1 = " << poly_2.evaluate(point_1) << std::endl;
    std::cout << "should be 0.5 = " << poly_3.evaluate(point_1) << std::endl;
    std::cout << "should be 0.5 = " << poly_4.evaluate(point_1) << std::endl;
    std::cout << "should be -1 = " << poly_5.evaluate(point_1) << std::endl;

    Model test_model = Model(points, fvalues, 2, 2);
    for (int i = 0; i < 6; ++i) {
        std::cout << "basis poly i = " << std::endl << test_model.get_basis().at(i).return_coeffs() << std::endl;
    }
    test_model.complete_points();

    std::cout << "points found are " << std::endl;
    for (int i = 0; i < 6; ++i) {
        std::cout << "point" << std::endl << test_model.get_points().at(i) << std::endl;
    }

    test_model.calculate_model_coeffs();

    Polynomial model_approx = Polynomial(2,test_model.get_model_coeffs());

    std::cout << "test to see if model approx is correct, i.e. M(x_i) = y(x_i)" << std::endl;

    for (int j = 0; j < 6; ++j) {
        std::cout << "M(x_" << j << ") = " << model_approx.evaluate(test_model.get_points().at(j)) << std::endl;
        std::cout << "y(x_" << j << ") = " << test_model.silly_function(test_model.get_points().at(j)) << std::endl;
    }

    Eigen::VectorXd testorino(2);
    testorino << 0,2;
    std::cout << "m(0,2) = " << model_approx.evaluate(testorino) << std::endl;

    return 0;
}