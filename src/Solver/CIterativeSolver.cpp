// Copyright (C) 2010 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include "Common/OptionT.hpp"
#include "Common/OptionURI.hpp"

#include "Solver/CIterativeSolver.hpp"

namespace CF {
namespace Solver {

using namespace Common;

////////////////////////////////////////////////////////////////////////////////

CIterativeSolver::CIterativeSolver ( const std::string& name  ) :
  CMethod ( name ),
  m_nb_iter(0)
{
  mark_basic();

  // properties

  properties()["brief"]=std::string("Iterative Solver component");
  properties()["description"]=std::string("Handles time stepping and convergence operations");

  m_properties.add_option<OptionT <Uint> >("Number of Iterations","Maximum number of iterations",m_nb_iter)->mark_basic();
  m_properties["Number of Iterations"].as_option().link_to( &m_nb_iter );

  m_properties.add_option< OptionURI > ("Domain", "Domain to solve", URI("cpath:../Domain"));

  // signals

  this->regist_signal ( "solve" , "Solves by executing a number of iterations", "Solve" )
      ->connect ( boost::bind ( &CIterativeSolver::signal_solve, this, _1 ) );
}

////////////////////////////////////////////////////////////////////////////////

CIterativeSolver::~CIterativeSolver()
{
}

////////////////////////////////////////////////////////////////////////////////

void CIterativeSolver::signal_solve ( Common::XmlNode& node )
{
  // XmlParams p ( node );

  this->solve(); // dispatch to the virtual function
}
////////////////////////////////////////////////////////////////////////////////

} // Solver
} // CF
