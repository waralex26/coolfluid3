// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#ifndef CF_Mesh_CTakeStep_hpp
#define CF_Mesh_CTakeStep_hpp

#include "Common/ComponentPredicates.hpp"

#include "Mesh/CFieldElements.hpp"
#include "Mesh/CTable.hpp"
#include "Mesh/CList.hpp"

#include "Actions/CNodeOperation.hpp"

#include "Solver/LibSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////

namespace CF {
namespace Solver {

///////////////////////////////////////////////////////////////////////////////////////

class Solver_API CTakeStep : public Actions::CNodeOperation
{
public: // typedefs

  /// pointers
  typedef boost::shared_ptr<CTakeStep> Ptr;
  typedef boost::shared_ptr<CTakeStep const> ConstPtr;

public: // functions
  /// Contructor
  /// @param name of the component
  CTakeStep ( const std::string& name );

  /// Virtual destructor
  virtual ~CTakeStep() {};

  /// Get the class name
  static std::string type_name () { return "CTakeStep"; }

  /// Set the loop_helper
  void create_loop_helper (Mesh::CElements& geometry_elements );
	
  /// @return the list to loop over, in this case the list of nodes.
  virtual Mesh::CList<Uint>& loop_list() const;
	
  /// execute the action
  virtual void execute ();
		
private: // data
	
  struct LoopHelper
  {
    LoopHelper(Mesh::CElements& geometry_elements, CLoopOperation& op) :
		solution(geometry_elements.get_field_elements(op.properties()["Solution Field"].value<std::string>()).data()),
		residual(geometry_elements.get_field_elements(op.properties()["Residual Field"].value<std::string>()).data()),
		inverse_updatecoeff(geometry_elements.get_field_elements(op.properties()["Inverse Update Coefficient"].value<std::string>()).data()),
		used_nodes(geometry_elements.get_field_elements(op.properties()["Solution Field"].value<std::string>()).used_nodes())
    { }
    Mesh::CTable<Real>& solution;
    Mesh::CTable<Real>& residual;
    Mesh::CTable<Real>& inverse_updatecoeff;
    Mesh::CList<Uint>&  used_nodes;
  };
	
  boost::shared_ptr<LoopHelper> m_loop_helper;

};

/////////////////////////////////////////////////////////////////////////////////////

} // Solver
} // CF

/////////////////////////////////////////////////////////////////////////////////////

#endif // CF_Mesh_CTakeStep_hpp
