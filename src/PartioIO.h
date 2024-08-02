/// @date 2024-08-02
/// @file PartioIO.h
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
/// 
/// @brief 
/// 
///
#include <Eigen/StdVector>

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