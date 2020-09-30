#ifndef PHYSICAL_NAMES_H
#define PHYSICAL_NAMES_H

#include <fstream>
#include <iostream>

#include <Eigen/Eigen>

class PhysicalNames
{
    private:
        int nbPhysicalNames_;

        std::vector<int> tag_;
        std::vector<std::string> names_;

    public:
        PhysicalNames();

        void Read_PhysicalNames(std::ifstream& mesh_file);

        inline const int& nbPhysicalNames() const { return nbPhysicalNames_; }
        inline const std::vector<int>& tag() const { return tag_; }
        inline const std::vector<std::string>& names() const { return names_; }

};

#endif