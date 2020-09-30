#ifndef __BIJECTIONELEMENTS_H__
#define __BIJECTIONELEMENTS_H__

#include <Eigen/Eigen>

class BijectionElements
{
public:
    static Eigen::VectorXd Biject
    (
        const int& dimension,
        const Eigen::MatrixXd &point_coord,
        const Eigen::VectorXd &ref_point_coord
    )
    {
        if (dimension == 2)
        {
            const double &x1 = point_coord(0, 0);
            const double &x2 = point_coord(1, 0);
            const double &x3 = point_coord(2, 0);
            const double &y1 = point_coord(0, 1);
            const double &y2 = point_coord(1, 1);
            const double &y3 = point_coord(2, 1);

            const double &ksi = ref_point_coord(0);
            const double &eta = ref_point_coord(1);

            Eigen::Vector2d vect;

            vect(0) = (x2 - x1) * ksi + (x3 - x1) * eta + x1;
            vect(1) = (y2 - y1) * ksi + (y3 - y1) * eta + y1;

            return vect;
        }

        if (dimension == 3)
        {
            const double &x1 = point_coord(0, 0);
            const double &x2 = point_coord(1, 0);
            const double &x3 = point_coord(2, 0);
            const double &x4 = point_coord(3, 0);
            const double &y1 = point_coord(0, 1);
            const double &y2 = point_coord(1, 1);
            const double &y3 = point_coord(2, 1);
            const double &y4 = point_coord(3, 1);
            const double &z1 = point_coord(0, 2);
            const double &z2 = point_coord(1, 2);
            const double &z3 = point_coord(2, 2);
            const double &z4 = point_coord(3, 2);

            const double &ksi = ref_point_coord(0);
            const double &eta = ref_point_coord(1);
            const double &epsilon = ref_point_coord(2);

            Eigen::Vector3d vect;

            vect(0) = (x2 - x1) * ksi + (x3 - x1) * eta + (x4 - x1) * epsilon + x1;
            vect(1) = (y2 - y1) * ksi + (y3 - y1) * eta + (y4 - y1) * epsilon + y1;
            vect(2) = (z2 - z1) * ksi + (z3 - z1) * eta + (z4 - z1) * epsilon + z1;

            return vect;
        }
        
        // throw;

    }
};

#endif // __BIJECTIONELEMENTS_H__