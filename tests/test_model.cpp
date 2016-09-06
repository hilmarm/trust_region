//
// Created by cutie on 25.08.16.
//

#include <gtest/gtest.h>
#include "../trust_lib/polynomial.h"
#include "../trust_lib/model.h"

namespace {

class ModelTest : public ::testing::Test {
protected:
    ModelTest() {
        int dim = 2;
        Eigen::VectorXd coeffs(6);
        coeffs << 0,0, 0, 1,1,1;
        Polynomial poly1 = Polynomial(dim, coeffs);

        Eigen::VectorXd point1(2), point2(2);
        point1 << 3,-3;
        point2 << 5, 0;
        //std::cout << "P(3,-3) = " << poly1.evaluate(point1) << std::endl;
        //std::cout << "P(5,0) = " << poly1.evaluate(point2) << std::endl;

        Eigen::VectorXd coeffs2(10);
        int dim2 = 3;
        coeffs2 << 0,1,0,0,0,1,0,0,1,0;
        Polynomial poly2 = Polynomial(dim2, coeffs2);

        Eigen::VectorXd point3(3);
        point3 << 1,-2, 120;
        //std::cout << "P(1,-2,120) = " << poly2.evaluate(point3) << std::endl;

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
    }

    virtual ~ModelTest() {
    }

    virtual void SetUp() {

    }

    virtual void TearDown() { }

};

TEST_F(ModelTest, Constructor) {
    EXPECT_TRUE(true);
}

TEST_F(ModelTest, poly_values) {
        Eigen::VectorXd pol_0(6), pol_1(6), pol_2(6), pol_3(6), pol_4(6), pol_5(6);
        pol_0 << 1,0,0,0,0,0;
        pol_1 << 0,1,0,0,0,0;
        pol_2 << 0,0,1,0,0,0;
        pol_3 << 0,0,0,1,0,0;
        pol_4 << 0,0,0,0,1,0;
        pol_5 << 0,0,0,0,0,1;

        Polynomial poly_0 = Polynomial(2,pol_0);
        Polynomial poly_1 = Polynomial(2,pol_1);
        Polynomial poly_2 = Polynomial(2,pol_2);
        Polynomial poly_3 = Polynomial(2,pol_3);
        Polynomial poly_4 = Polynomial(2,pol_4);
        Polynomial poly_5 = Polynomial(2,pol_5);
        Eigen::VectorXd point_1(2);
        point_1 << 1, -1;

        EXPECT_EQ(poly_0.evaluate(point_1),1);
        EXPECT_EQ(poly_1.evaluate(point_1),1);
        EXPECT_EQ(poly_2.evaluate(point_1),-1);
        EXPECT_EQ(poly_3.evaluate(point_1),.5);
        EXPECT_EQ(poly_4.evaluate(point_1),.5);
        EXPECT_EQ(poly_5.evaluate(point_1),-1);

}

    TEST_F(ModelTest, gradient_values) {
        Eigen::VectorXd pol_0(6), pol_1(6), pol_2(6), grad_0(2), grad_1(2), grad_2(2), point(2);
        pol_0 << 499,0,0,4,0,0;
        pol_1 << -2,-3,43,0,0,0;
        pol_2 << 0,3,0,0,0,12;

        grad_0 << 4,0;
        grad_1 << -3, 43;
        grad_2 << 15, 12;
        point << 1,1;

        Polynomial poly_0 = Polynomial(2,pol_0);
        Polynomial poly_1 = Polynomial(2,pol_1);
        Polynomial poly_2 = Polynomial(2,pol_2);

        EXPECT_TRUE(poly_0.evaluateGradient(point)==grad_0);
        EXPECT_TRUE(poly_1.evaluateGradient(point)==grad_1);
        EXPECT_TRUE(poly_2.evaluateGradient(point)==grad_2);
    }

}
