#include <vector>

struct charge {
    double q = 0;
    double x = 0;
    double y = 0;
};


class potential_computing {
public:
    potential_computing(unsigned x, unsigned y) {
        std::vector<double> temp(x, 0);
        m_matrix = t_matrix(y, temp);
    }

    using t_matrix = std::vector<std::vector<double>>;

    void init_charge(charge q);
    void compute();
    const t_matrix& get_matrix() const;

private:
    t_matrix m_matrix;
    std::vector<charge> m_charges;
};
