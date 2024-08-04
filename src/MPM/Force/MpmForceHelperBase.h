#ifndef MPM_FORCE_HELPER_BASE_H
#define MPM_FORCE_HELPER_BASE_H

#include <Ziran/CS/DataStructure/DisjointRanges.h>
#include <Ziran/CS/Util/AttributeNamesForward.h>
#include <Ziran/Physics/PlasticityApplier.h>
#include <MPM/Forward/MpmForward.h>

namespace ZIRAN {

template <class T, int dim>
class MpmForceHelperBase {
public:
    typedef Matrix<T, dim, dim> TM;
    typedef Vector<T, dim> TV;
    using TVStack = Matrix<T, dim, Eigen::Dynamic>;

    virtual ~MpmForceHelperBase() {}
    virtual void backupStrain() {}
    virtual void restoreStrain() {}
    virtual void updateState(const DisjointRanges& subrange, StdVector<TM>& vtau, TVStack& fp) {}
    virtual void updateImplicitState(const DisjointRanges& subrange, StdVector<TM>& vPFnT, TVStack& fp) {}

    virtual bool needGradVn() { return false; }
    virtual void getGradVn(const StdVector<TM>& gradVn) {}

    virtual void evolveStrain(const DisjointRanges& subrange, T dt, const StdVector<TM>& gradV) {}
    virtual double totalEnergy(const DisjointRanges& subrange) { return 0.0; }
    virtual void reinitialize() {}

    // the input is gradDV, the output is V_p^0 dP (F_p^n)^T (dP is Ap in snow paper)
    virtual void computeStressDifferential(const DisjointRanges& subrange, const StdVector<TM>& gradDv, StdVector<TM>& dstress, const TVStack& dvp, TVStack& dfp) {}

    virtual void computeStressDifferentialWithPlasticity(const DisjointRanges& subrange, const StdVector<TM>& gradDv, StdVector<TM>& dstress) { ZIRAN_ASSERT(false, "not implemented"); }

    using Hessian = Eigen::Matrix<T, dim * dim, dim * dim>;
    virtual void runLambdaWithDifferential(
        const StdVector<int>& particle_order,
        const std::vector<std::pair<int, int>>& particle_group,
        const std::vector<uint64_t>& block_offset,
        std::function<void(int, const Hessian&, const TM&, const T&, const T&, bool)> func, int opt = 0) {} ///< opt 0: default 1: store dPdF 2: reuse dPdF
    virtual void computePerNodeCNTolerance(
        const StdVector<int>& particle_order,
        const std::vector<std::pair<int, int>>& particle_group,
        const std::vector<uint64_t>& block_offset,
        std::function<void(int, const Hessian&, const T&, bool)> func){};
};
} // namespace ZIRAN
#endif
