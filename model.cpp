//
// Created by hilmarm on 13.07.16.
//

#include "model.h"

Model::Model(QList<Eigen::VectorXd> points, QList<double> fvalues, double radius, QList<Polynomial> basis){
    points_ = points;
    fvalues_ = fvalues;
    center_ = points.at(0);
    radius_ = radius;
    basis_ = basis;
}

QList<Eigen::VectorXd> Model::get_points() const{
    return points_;
}

QList<double> Model::get_fvalues() const{
    return fvalues_;
}

double Model::get_radius() const{
    return radius_;
}

QList<Polynomial> Model::get_basis() const{
    return basis_;
}

Eigen::VectorXd Model::get_model_coeffs() const {
    return model_coeffs_;
}

void Model::complete_points() {
    // Complete set of interpolation points so
    // that the set is well-poised

    /* Pivot element tolerance. Note that we can always find
     * an element inside the ball of radius one so that the
     * value is at least 0.25. It might however be clever to
     * lower this tolerance in order to preserve as many stored
     * function evaluations as possible.
     */
    double tol_pivot = 0.24;
    Eigen::VectorXd centre_point = points_.at(0);

    /* scaling points to a ball of radius 1
     * and center at center_ (first point of
     * the points list)
     */
    double max_norm = 0;
    for(int i=1; i<points_.length(); i++){
        Eigen::VectorXd diff = points_.at(i) - centre_point;
        if(diff.norm() > max_norm){
            max_norm = diff.norm();
        }
    }
    std::cout << "max norm = " << max_norm << std::endl;
    if(max_norm==0){
        max_norm = 1;
        std::cout << "all points are the same point or only 1 point in set" << std::endl;
    }

    QList<Eigen::VectorXd> points_abs;
    for (int i = 0; i < points_.length(); ++i) {
        //Eigen::VectorXd diff_vec = (1/max_norm)*(get_points().at(i)-get_points().at(0));//points_.at(i)-points_.at(0);
        points_abs.append((1/max_norm)*(get_points().at(i) - centre_point));
    }

    int n_Polynomials = basis_.length();
    int n_points = points_.length();

    for(int i=0; i<n_Polynomials; i++){
        Polynomial cur_pol = basis_.at(i);
        double max_abs = 0.0;
        int max_abs_ind = -1;

        for (int j = i; j < n_points; ++j) {
            if(fabs(cur_pol.evaluate(points_abs.at(j)))>max_abs){
                max_abs = fabs(cur_pol.evaluate(points_abs.at(j)));
                max_abs_ind = j;
            }
        }

        // If evaluation in pivot element is greater than treshold, switch elements.
        if(max_abs>tol_pivot){
            points_abs.swap(i,max_abs_ind);
            std::cout << "YES sufficent pivot element aka. good point" << std::endl;
        }
        else{
            //Find new point using alg proposed by Conn
            std::cout << "NO sufficent pivot element aka. good point, use CONN alg" << std::endl;
            Polynomial temp_poly_here = basis_.at(i);
            //std::cout << find_new_point(temp_poly_here) << std::endl;
            points_abs.append(find_new_point(temp_poly_here));
            points_abs.swap(i,points_abs.length()-1);
            std::cout << "new point found with value = " << temp_poly_here.evaluate(points_abs.at(i)) << std::endl;
        }

        Polynomial temp_i = basis_.at(i);
        auto temp_point = points_abs.at(i);


        for (int j = i+1; j <n_points ; j++) {
            Polynomial uj= basis_.at(j);
            Polynomial ui = basis_.at(i);
            double temp_ratio = uj.evaluate(temp_point)/ui.evaluate(temp_point);
            ui.multiply(-1.0*temp_ratio);
            uj.add(ui);
            basis_[j] = uj;
        }
    }

    // Scale points back
    QList<Eigen::VectorXd> points_scaled;
    for (int i = 0; i < n_Polynomials; ++i) {
        points_scaled.append(centre_point + max_norm*points_abs.at(i));
    }

    points_ = points_abs;
}

Eigen::VectorXd Model::find_new_point(Polynomial poly) const {
// As described by A. Conn, finds a 'good point' for the scaled trust region.
    // This is a copy of C. Giuliani's Matlab code

    int dimension = poly.return_dimension();
    Eigen::VectorXd coeffs = poly.return_coeffs();
    Eigen::VectorXd x0, x1, x2, x3, x4;
    x0 = x1 = x2 = x3 = x4 = Eigen::VectorXd::Zero(dimension);

    // Find largest monomial coefficient (excluding constant term which has already been assigned to first point)
    double max = 0.0;
    int max_coeff = -1;
    std::cout << x0 << std::endl;
    for (int i = 1; i < poly.return_no_elements(); ++i) {
        if(fabs(coeffs(i)) > max) {
            max = fabs(coeffs(i));
            max_coeff = i;
        }
    }
    if(max_coeff==-1){ std::cout << "Good point alg, Problem: all coefficients are zero" << std::endl;}
    std::cout << "max coeff = " << max_coeff<< std::endl;
    std::cout << "dimension = " << dimension << std::endl;
    if(max_coeff<=dimension){
        // The largest coefficient is from a linear term
        x1(max_coeff-1) = 1; //subract 1 maybe if change polynomial form
        x2 = -x1;
    }
    else if(max_coeff<=2*dimension){
        // Largest coefficient is quadratic monomial
        x1(max_coeff-dimension-1) = 1;
        x2 = -x1;
    }
    else{
        // Mixed term quadratic is larges
        // There is probably a smarter way to do this... oh whatever I'm lazy
        int l,m = 0;
        int coeff_dummy = 2*dimension+1;

        for(int i=0; i<dimension-1; i++){
            for (int j=1; j<dimension; j++) {
                if (max_coeff == coeff_dummy) {
                    l = i;
                    m = j;
                    break;
                }
                coeff_dummy = coeff_dummy+1;
            }
        }

        x1(l) =  1.0/sqrt(2);
        x1(m) = -1.0/sqrt(2);
        x2 = -x1;
        for(int i=0; i<dimension; i++){
            x3(i) = fabs(x1(i));
            x4(i) = -fabs(x1(i));
        }
    }
    Eigen::VectorXd best_point;
    double best_value = 0;
    QList<Eigen::VectorXd> points;
    points.append(x0);
    points.append(x1);
    points.append(x2);
    points.append(x3);
    points.append(x4);
    for(int i=0; i<5; i++){
        if(fabs(poly.evaluate(points.at(i)))>=best_value){
            best_point = points.at(i);
            best_value = fabs(poly.evaluate(points.at(i)));
        }
    }
    std::cout << "Ended finding point" << std::endl << best_point << "and value is = " << best_value << std::endl;

    return best_point;
}

void Model::calculate_model_coeffs() {
    

}



