// Copyright (C) 2010-2011 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

#include <boost/bind.hpp>
#include <boost/function.hpp>

#include "common/Core.hpp"
#include "common/FindComponents.hpp"
#include "common/Foreach.hpp"
#include "common/Log.hpp"
#include "common/OptionList.hpp"
#include "common/Signal.hpp"
#include "common/Builder.hpp"
#include "common/OptionT.hpp"
#include <common/EventHandler.hpp>

#include "math/LSS/System.hpp"

#include "mesh/Region.hpp"
#include "mesh/LagrangeP0/LibLagrangeP0.hpp"
#include "mesh/LagrangeP0/Quad.hpp"
#include "mesh/LagrangeP0/Line.hpp"

#include "BCWallFunctionNSImplicit.hpp"
#include "AdjacentCellToFace.hpp"
#include "Tags.hpp"

#include "solver/actions/Proto/ProtoAction.hpp"
#include "solver/actions/Proto/Expression.hpp"


namespace cf3
{

namespace UFEM
{

using namespace solver::actions::Proto;

////////////////////////////////////////////////////////////////////////////////////////////

common::ComponentBuilder < BCWallFunctionNSImplicit, common::Action, LibUFEM > BCWallFunctionNSImplicit_Builder;

////////////////////////////////////////////////////////////////////////////////////////////

using boost::proto::lit;

BCWallFunctionNSImplicit::BCWallFunctionNSImplicit(const std::string& name) :
  Action(name),
  rhs(options().add("lss", Handle<math::LSS::System>())
    .pretty_name("LSS")
    .description("The linear system for which the boundary condition is applied")),
  system_matrix(options().option("lss"))
{
  options().add("tau_wall", m_tau_wall)
    .pretty_name("Tau Wall")
    .description("Wall shear stress")
    .link_to(&m_tau_wall)
    .mark_basic();

  create_static_component<ProtoAction>("WallLaw")->options().option("regions").add_tag("norecurse");

  trigger_setup();
}

BCWallFunctionNSImplicit::~BCWallFunctionNSImplicit()
{
}


void BCWallFunctionNSImplicit::on_regions_set()
{
  get_child("WallLaw")->options().set("regions", options()["regions"].value());
}

void BCWallFunctionNSImplicit::trigger_setup()
{
  Handle<ProtoAction> wall_law(get_child("WallLaw"));

  FieldVariable<0, VectorField> u("Velocity", "navier_stokes_solution");
  FieldVariable<1, ScalarField> p("Pressure", "navier_stokes_solution");
  FieldVariable<2, ScalarField> nu_eff("EffectiveViscosity", "navier_stokes_viscosity");

  const auto u_norm = make_lambda([&](const Real u_norm_in)
  {
    if(u_norm_in < 1e-10)
    {
      return 1.;
    }

    return u_norm_in;
  });

  // Set normal component to zero
  wall_law->set_expression(elements_expression
  (
    boost::mpl::vector1<mesh::LagrangeP1::Line2D>(), // Valid for surface element types
    group
    (
      _A(u) = _0, _A(p) = _0,
      element_quadrature
      (
        _A(p, u[_i]) += -transpose(N(p)) * N(u) * normal[_i], // no-penetration condition
        _A(u[_i], u[_i]) += transpose(N(u)) * lit(m_tau_wall) * N(u) / u_norm(_norm(u))
      ),
      system_matrix +=  _A,
      rhs += -_A * _x
    )
  ));
}

void BCWallFunctionNSImplicit::execute()
{
  Handle<ProtoAction> wall_law(get_child("WallLaw"));

  wall_law->execute();
}

} // namespace UFEM

} // namespace cf3