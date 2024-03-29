#include "modelinterface2_pin.h"

#include <pinocchio/algorithm/rnea.hpp>

using namespace XBot;

VecConstRef ModelInterface2Pin::computeInverseDynamics() const
{
    if(!(_cached_computation & Rnea))
    {

        _tmp.rnea = pinocchio::rnea(_mdl, _data,
                                    getJointPosition(),
                                    getJointVelocity(),
                                    getJointAcceleration());


        _cached_computation |= Rnea;

    }

    return _tmp.rnea;
}

VecConstRef ModelInterface2Pin::computeGravityCompensation() const
{
    if(!(_cached_computation & Gcomp))
    {

        _tmp.gcomp = pinocchio::computeGeneralizedGravity(_mdl, _data,
                                                         getJointPosition());


        _cached_computation |= Gcomp;

    }

    return _tmp.gcomp;
}

VecConstRef ModelInterface2Pin::computeNonlinearTerm() const
{
    if(!(_cached_computation & NonlinearEffects))
    {
        _tmp.h = pinocchio::nonLinearEffects(_mdl, _data,
                                             getJointPosition(), getJointVelocity());

        _cached_computation |= NonlinearEffects;

    }

    return _tmp.h;
}
