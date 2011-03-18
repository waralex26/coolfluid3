// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef CF_FVM_FiniteVolumeSolver2D_hpp
#define CF_FVM_FiniteVolumeSolver2D_hpp

////////////////////////////////////////////////////////////////////////////////

#include "Solver/CSolver.hpp"

#include "FVM/ComputeUpdateCoefficient.hpp"
#include "FVM/LibFVM.hpp"

namespace CF {

namespace Common {
  class CAction;
  class CLink;
  class Signal;
}
namespace Solver { 
  namespace Actions { 
    class CIterate;     
  }
}

namespace Mesh {
  class CField2;
  class CRegion;
}

namespace FVM {
  class ComputeUpdateCoefficient;
  class UpdateSolution;

////////////////////////////////////////////////////////////////////////////////

/// RKRD iterative solver
/// @author Tiago Quintino
/// @author Willem Deconinck
class FVM_API FiniteVolumeSolver2D : public Solver::CSolver {

public: // typedefs

  typedef boost::shared_ptr<FiniteVolumeSolver2D> Ptr;
  typedef boost::shared_ptr<FiniteVolumeSolver2D const> ConstPtr;

public: // functions

  /// Contructor
  /// @param name of the component
  FiniteVolumeSolver2D ( const std::string& name );

  /// Virtual destructor
  virtual ~FiniteVolumeSolver2D();

  /// Get the class name
  static std::string type_name () { return "FiniteVolumeSolver2D"; }

  // functions specific to the FiniteVolumeSolver2D component
  
  virtual void solve();
  
  /// @name SIGNALS
  //@{

  /// creates a boundary condition
  void signal_create_bc( Common::SignalArgs& xml );

  //@} END SIGNALS


  Common::CAction& create_bc(const std::string& name, const std::vector<boost::shared_ptr<Mesh::CRegion> >& regions, const std::string& bc_builder_name);
  Common::CAction& create_bc(const std::string& name, const Mesh::CRegion& region, const std::string& bc_builder_name);

  
private: // functions

  void trigger_Domain();

private: // data
  
  boost::shared_ptr<Common::CLink> m_solution;
  boost::shared_ptr<Common::CLink> m_residual;
  boost::shared_ptr<Common::CLink> m_wave_speed;
  boost::shared_ptr<Common::CLink> m_update_coeff;

  boost::shared_ptr<Solver::Actions::CIterate> m_iterate;
  boost::shared_ptr<Common::CAction> m_apply_bcs;
  boost::shared_ptr<Common::CAction> m_compute_rhs;
  boost::shared_ptr<ComputeUpdateCoefficient> m_compute_update_coefficient;
  boost::shared_ptr<UpdateSolution> m_update_solution;

};

////////////////////////////////////////////////////////////////////////////////

} // FVM
} // CF

////////////////////////////////////////////////////////////////////////////////

#endif // CF_FVM_FiniteVolumeSolver2D_hpp