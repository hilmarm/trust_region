//
// Created by cutie on 25.08.16.
//

#include <gtest/gtest.h>
#include "../trust_lib/polynomial.h"

namespace {

    class PolynomTest : public ::testing::Test {
    protected:
        PolynomTest() { }

        virtual ~PolynomTest() {
        }

        virtual void SetUp() {
            d=2.94;

        }

        virtual void TearDown() { }

        double d;

    };

    TEST_F(PolynomTest, Constructor) {
        Eigen::VectorXd coeffs(6);
        int dim = 2;
        coeffs << 0, 0, 0, 1,1,1;
        Polynomial poly1 = Polynomial(dim, coeffs);
        EXPECT_TRUE(true);
    }

    TEST_F(PolynomTest, bogofail) {
        Eigen::VectorXd vec(2);
        EXPECT_TRUE(true);
    }

}
