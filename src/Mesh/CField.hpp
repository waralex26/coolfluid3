#ifndef CF_Mesh_CField_hpp
#define CF_Mesh_CField_hpp

////////////////////////////////////////////////////////////////////////////////

#include "Common/Component.hpp"
#include "Common/ComponentPredicates.hpp"

#include "Mesh/MeshAPI.hpp"

#include "Mesh/CElements.hpp"
#include "Mesh/CArray.hpp"


namespace CF {
namespace Common 
{
  class CLink;
}
namespace Mesh {
  
  class CRegion;

////////////////////////////////////////////////////////////////////////////////

/// Field component class
/// This class stores fields which can be applied 
/// to fields (Cfield)
/// @author Willem Deconinck, Tiago Quintino
class Mesh_API CField : public Common::Component {

public: // typedefs

  typedef boost::shared_ptr<CField> Ptr;
  typedef boost::shared_ptr<CField const> ConstPtr;
  
  enum DataBasis { ELEMENT_BASED=0,  NODE_BASED=1};

public: // functions

  /// Contructor
  /// @param name of the component
  CField ( const CName& name );

  /// Virtual destructor
  virtual ~CField();

  /// Get the class name
  static std::string type_name () { return "CField"; }

  /// Configuration Options
  static void defineConfigOptions ( Common::OptionList& options ) {}

  // functions specific to the CField component
  
  /// create a Cfield component
  /// @param name of the field
  CField& synchronize_with_region(CRegion& support, const std::string& field_name = "");

  void create_data_storage(const Uint dim, const DataBasis basis);

  /// create a CElements component, initialized to take connectivity data for the given type
  /// @param name of the field
  /// @param element_type_name type of the elements
  CElements& create_elements (CElements& geometry_elements);
  
  /// create a coordinates component, initialized with the coordinate dimension
  /// @param name of the field
  /// @param element_type_name type of the elements  
  CArray& create_data(const Uint dim, const Uint nb_rows);
  
  const CRegion& support() const;
  CRegion& support();
  
  /// @return the number of elements stored in this field, including any subfields
  Uint recursive_elements_count() const
  {
    Uint elem_count = 0;
    BOOST_FOREACH(const CElements& elements, recursive_range_typed<CElements>(*this))
    {
      elem_count += elements.elements_count();
    }
    return elem_count;
  }
  
  /// @return the number of elements stored in this field, including any subfields
  template <typename Predicate>
  Uint recursive_filtered_elements_count(const Predicate& pred) const
  {
    Uint elem_count = 0;
    BOOST_FOREACH(const CElements& elements, recursive_filtered_range_typed<CElements>(*this,pred))
    {
      elem_count += elements.elements_count();
    }
    return elem_count;
  }
  
  std::string field_name() const { return m_field_name; }
  
  /// @return the field with given name
  const CField& subfield(const CName& name) const;
  
  /// @return the field with given name
  CField& subfield(const CName& name);
  
  /// @return the elements with given name
  const CFieldElements& elements (const CName& element_type_name) const;
  
  /// @return the elements with given name
  CFieldElements& elements (const CName& element_type_name);
  
  
private: // helper functions

  /// regists all the signals declared in this class
  static void regist_signals ( Component* self ) {}

private:
  
  std::string m_field_name;

};

////////////////////////////////////////////////////////////////////////////////

} // Mesh
} // CF

////////////////////////////////////////////////////////////////////////////////

#endif // CF_Mesh_CField_hpp
