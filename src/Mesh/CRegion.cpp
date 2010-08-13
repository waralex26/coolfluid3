#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

#include "Common/CGroup.hpp"
#include "Common/CLink.hpp"

#include "Mesh/CRegion.hpp"
#include "Mesh/CField.hpp"
#include "Mesh/CElements.hpp"
#include "Mesh/CTable.hpp"
#include "Mesh/CArray.hpp"

namespace CF {
namespace Mesh {

using namespace Common;

////////////////////////////////////////////////////////////////////////////////

CRegion::CRegion ( const CName& name  ) :
  Component ( name )
{
  BUILD_COMPONENT;
}

////////////////////////////////////////////////////////////////////////////////

CRegion::~CRegion()
{
}

////////////////////////////////////////////////////////////////////////////////

CRegion& CRegion::create_region( const CName& name )
{
  CRegion& region = *create_component_type<CRegion>(name);
  return region;
}

////////////////////////////////////////////////////////////////////////////////

CElements& CRegion::create_elements(const std::string& element_type_name, CArray& coordinates)
{
  std::string name = "elements_" + element_type_name;
  CElements& elements = *create_component_type<CElements>(name);

  elements.initialize(element_type_name,coordinates);
  return elements;
}

//////////////////////////////////////////////////////////////////////////////

CArray& CRegion::create_coordinates(const Uint& dim)
{
  CArray& coordinates = *create_component_type<CArray>("coordinates");
  coordinates.initialize(dim);
  return coordinates;
}
  
//////////////////////////////////////////////////////////////////////////////

void CRegion::add_field_link(CField& field)
{
  CGroup::Ptr field_group = get_child_type<CGroup>("fields");
  if (!field_group.get())
    field_group = create_component_type<CGroup>("fields");
  field_group->create_component_type<CLink>(field.field_name())->link_to(field.get());
}
  
//////////////////////////////////////////////////////////////////////////////

CField& CRegion::get_field(const CName& field_name)
{
  Component::Ptr all_fields = get_child("fields");
  cf_assert(all_fields.get());
  Component::Ptr field = all_fields->get_child(field_name);
  cf_assert(field.get());
  return *boost::dynamic_pointer_cast<CField>(field->get());
}

//////////////////////////////////////////////////////////////////////////////
  
Uint CRegion::recursive_elements_count() const
{
  Uint elem_count = 0;
  BOOST_FOREACH(const CElements& elements, recursive_range_typed<CElements>(*this))
    elem_count += elements.elements_count();
  return elem_count;
}

//////////////////////////////////////////////////////////////////////////////


} // Mesh
} // CF
