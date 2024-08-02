// RunAdder.cpp
#include "Adder.h"
#include <tbb/tbb.h>
#include <Eigen/StdVector>
#include <pugixml.hpp>
#include <fstream>
#include <VtkIO.h>

#include <CS/Util/DataDir.h>

template <typename T, int dim>
using Vector = Eigen::Matrix<T, dim, 1, 0, dim, 1>;


template <typename Type>
using StdVector = std::vector<Type, Eigen::aligned_allocator<Type>>;


/**
   Suppose that you have StdVector<Vector<T, dim>> particle_positions that
   store the position of the particles
   Use this function to write these positions into bgeo.
   Example:
   StdVector<EigenTV> samples;
   std::string filename = "test.bgeo";
   writePositionVectorToPartio(filename, samples);
*/
template <class T, int dim>
void writePositionVectorToPartio(const std::string& particleFile,
    const StdVector<Vector<T, dim>>& particles)
{
    Partio::ParticlesDataMutable* parts = Partio::create();
    Partio::ParticleAttribute posH;
    posH = parts->addAttribute("position", Partio::VECTOR, 3);
    for (size_t iter = 0; iter < particles.size(); ++iter) {
        int idx = parts->addParticle();
        float* p = parts->dataWrite<float>(posH, idx);
        for (int k = 0; k < 3; k++)
            p[k] = (T)0;
        for (int k = 0; k < dim; k++)
            p[k] = particles[iter](k);
    }
    Partio::write(particleFile.c_str(), *parts);
    parts->release();
}


int main() {
    ZIRAN::DataDir output_dir{};
    std::string obj_filename = output_dir.absolutePath(ZIRAN::outputFileName("partio", ".vtk"));

    // 示例数据：一个包含几个三维点的 std::vector
    std::vector<std::array<double, 3>> points = {
        {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0},
        {1.0, 1.0, 0.0},
        {0.0, 1.2, 0.0},
        {0.0, 1.3, 0.0},
        {0.0, 1.4, 0.0},
        {0.0, 1.5, 0.0},
        {0.5, 0.5, 1.0}
    };
    writePositionVectorToVtk(obj_filename,points);
    return 0;
}


// int main() {
//     Adder adder;
//     adder.print_value(std::cout);
//     adder.add(5);
//     adder.print_value(std::cout);
//     adder.add(5);
//     adder.print_value(std::cout);
//     adder.clear();

//     // StdVector<Eigen::EigenTV> samples;
//     // std::string filename = "test.bgeo";
//     // writePositionVectorToPartio(filename, samples);
//     pugi::xml_document doc;
//     pugi::xml_parse_result result = doc.load_file("xgconsole.xml");
//     if (!result)
//         return -1;
        
//     for (pugi::xml_node tool: doc.child("Profile").child("Tools").children("Tool"))
//     {
//         int timeout = tool.attribute("Timeout").as_int();
        
//         if (timeout > 0)
//             std::cout << "Tool " << tool.attribute("Filename").value() << " has timeout " << timeout << "\n";
//     }
//     return 0;
// }
