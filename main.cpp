#include <iostream>
#include "region.h"
#include "model.h"
#include "polynomial.h"
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
    point_2 << 1, 0;
    point_3 << 0, 0.01;
    point_4 << 0, -1;
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


    std::cout << "should be 1 = " << poly_0.evaluate(point_0) << std::endl;
    std::cout << "should be 0 = " << poly_1.evaluate(point_0) << std::endl;
    std::cout << "should be -1 = " << poly_2.evaluate(point_0) << std::endl;
    std::cout << "should be 0 = " << poly_3.evaluate(point_0) << std::endl;
    std::cout << "should be 0.5 = " << poly_4.evaluate(point_0) << std::endl;
    std::cout << "should be 0 = " << poly_5.evaluate(point_0) << std::endl;

    Model test_model = Model(points, fvalues, 2, basis);
    //std::cout << test_model.get_points().at(3) << std::endl;
    test_model.complete_points();
    //auto silly = test_model.get_basis().at(3);
    //for (int i = 0; i <4 ; ++i) {
    //    std::cout << "should be zero = " << silly.evaluate(test_model.get_points().at(i)) << std::endl;
    //}

    poly_0.add(poly_1);
    poly_0.multiply(44);
    std::cout << poly_0.return_coeffs() << std::endl;


    return 0;
}