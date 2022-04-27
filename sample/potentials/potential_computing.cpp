
#include "potential_computing.h"
#include <cmath>
#include <iostream>

namespace rocky::sample {

    void potential_computing::init_charge(charge q) {
        m_charges.push_back(q);
    }
    
    void potential_computing::compute() {
        for(auto i_y = 0; i_y < m_matrix.size(); i_y++) {
            for(auto i_x = 0; i_x < m_matrix[i_y].size(); i_x++) {
                double sum = 0;
                for(auto&& q: m_charges) {
                    if(std::abs(i_x - q.x) < 0.5 && std::abs(i_y - q.y) < 0.5){
                        sum = 1000 * q.q;
                        break;
                    } else {
                        sum += q.q / (std::sqrt(pow(i_x - q.x, 2) + pow(i_y - q.y, 2)));
                    }
                }
                m_matrix[i_y][i_x] = sum;
            }
        }
    }
    
    const potential_computing::t_matrix& potential_computing::get_matrix() const{
        return m_matrix;
    }

}