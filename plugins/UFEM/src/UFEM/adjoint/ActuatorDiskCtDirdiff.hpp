// Copyright (C) 2010-2011 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef cf3_UFEM_ActuatorDiskCtDirdiff_hpp
#define cf3_UFEM_ActuatorDiskCtDirdiff_hpp


#include "../UnsteadyAction.hpp"
#include "solver/actions/Proto/BlockAccumulator.hpp"

#include "LibUFEMAdjoint.hpp"


namespace cf3 {
namespace UFEM {
namespace adjoint {

class UFEM_API ActuatorDiskCtDirdiff : public UnsteadyAction
{
public:

  /// Contructor
  /// @param name of the component
  ActuatorDiskCtDirdiff ( const std::string& name );

  virtual ~ActuatorDiskCtDirdiff();

  /// Get the class name
  static std::string type_name () { return "ActuatorDiskCtDirdiff"; }

  /// Execute the control of heat transfer coefficient usage (dynamic or static)
  virtual void execute();

private:
  /// Called when the boundary regions are set
  virtual void on_regions_set();

  /// Called when an option that requires a rebuild of the expression is changed
  void trigger_setup();

  Real m_area = 0.;
  Real m_SensF = 0.;
  Real m_a = 0.;
  Real m_ct = 0.;
  Real m_th = 0.;
  // Real m_SensU_mean_disk = 0.;
  int m_NDiscs =0;
  Real m_SensU_mean_disk;

  cf3::solver::actions::Proto::SystemRHS rhs;
  cf3::solver::actions::Proto::SystemMatrix system_matrix;
};

} // adjoint
} // UFEM
} // cf3


#endif // cf3_UFEM_ActuatorDiskCtDirdiff_hpp
