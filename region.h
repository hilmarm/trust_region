//
// Created by hilmarm on 30.06.16.
//

#ifndef TRUST_REGION_ALG_REGION_H
#define TRUST_REGION_ALG_REGION_H

class region {

private:
    double obj_f_(double i, double j);
    double current_eval_;
    int index_;

public:
    region(int index);
    int return_index();
    double eval_f(double i, double j);

};


#endif //TRUST_REGION_ALG_REGION_H
