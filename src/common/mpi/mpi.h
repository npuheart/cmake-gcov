//// @date 2024-08-25
/// @file mpi.h
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief all_gather and gather functions for MPI
///
///

#pragma once
#include <dolfinx.h>
#include <numeric>
#include <petsc.h>
#include <vector>

/// Some are copied from legacy DOLFIN
/// Gather values on one process
namespace npuheart {
namespace mpi {

enum class Petsc_Status {
    INITIALIZED, // 表示 PETSc 已初始化
    FINALIZED    // 表示 PETSc 已终止
};

inline void check_mpi(Petsc_Status status, int argc, char** argv) {
    (void)argc;
    (void)argv;
    if (status == Petsc_Status::INITIALIZED) {
        PetscBool isInitialized;
        PetscInitialized(&isInitialized);
        if (!isInitialized) {
            spdlog::info("MPI is not initialized. Initializing MPI now.");
            PetscInitialize(&argc, &argv, nullptr, nullptr);
        } else {
            spdlog::info("MPI is already initialized.");
        }
    }

    if (status == Petsc_Status::FINALIZED) {
                
        PetscBool isFinalized;
        PetscFinalized(&isFinalized);
        if (!isFinalized) {
            spdlog::info("MPI is not finalized. Finalizing MPI now.");
            PetscFinalize();
        } else {
            spdlog::info("MPI is already finalized.");
        }
    }
}

/// MPI Type
template <typename T>
constexpr MPI_Datatype mpi_type() {
    if constexpr (std::is_same_v<T, float>)
        return MPI_FLOAT;
    else if constexpr (std::is_same_v<T, double>)
        return MPI_DOUBLE;
    else if constexpr (std::is_same_v<T, std::complex<double>>)
        return MPI_C_DOUBLE_COMPLEX;
    else if constexpr (std::is_same_v<T, std::complex<float>>)
        return MPI_C_FLOAT_COMPLEX;
    else if constexpr (std::is_same_v<T, short int>)
        return MPI_SHORT;
    else if constexpr (std::is_same_v<T, int>)
        return MPI_INT;
    else if constexpr (std::is_same_v<T, unsigned int>)
        return MPI_UNSIGNED;
    else if constexpr (std::is_same_v<T, long int>)
        return MPI_LONG;
    else if constexpr (std::is_same_v<T, unsigned long>)
        return MPI_UNSIGNED_LONG;
    else if constexpr (std::is_same_v<T, long long>)
        return MPI_LONG_LONG;
    else if constexpr (std::is_same_v<T, unsigned long long>)
        return MPI_UNSIGNED_LONG_LONG;
    else if constexpr (std::is_same_v<T, bool>)
        return MPI_C_BOOL;
    else if constexpr (std::is_same_v<T, std::int8_t>)
        return MPI_INT8_T;
    else
        // Issue compile time error
        static_assert(!std::is_same_v<T, T>);
}

template <template <typename> class ContainerType, typename T>
void gather(MPI_Comm comm, const ContainerType<T>& in_values, std::vector<T>& out_values,
            unsigned int receiving_process) {
    const std::size_t comm_size = MPI::size(comm);

    // Get data size on each process
    std::vector<int> pcounts(comm_size);
    const int        local_size = in_values.size();
    MPI_Gather(const_cast<int*>(&local_size), 1, mpi_type<int>(), pcounts.data(), 1, mpi_type<int>(), receiving_process,
               comm);

    // Build offsets
    std::vector<int> offsets(comm_size + 1, 0);
    for (std::size_t i = 1; i <= comm_size; ++i)
        offsets[i] = offsets[i - 1] + pcounts[i - 1];

    const std::size_t n = std::accumulate(pcounts.begin(), pcounts.end(), 0);
    out_values.resize(n);
    MPI_Gatherv(const_cast<T*>(in_values.data()), in_values.size(), mpi_type<T>(), out_values.data(), pcounts.data(),
                offsets.data(), mpi_type<T>(), receiving_process, comm);
}

template <typename T>
void all_gather(MPI_Comm comm, const std::vector<T>& in_values, std::vector<T>& out_values) {
    out_values.resize(in_values.size() * MPI::size(comm));
    MPI_Allgather(const_cast<T*>(in_values.data()), in_values.size(), mpi_type<T>(), out_values.data(),
                  in_values.size(), mpi_type<T>(), comm);
}
} // namespace mpi
} // namespace npuheart