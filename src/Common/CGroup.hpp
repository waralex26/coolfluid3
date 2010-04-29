#ifndef CF_Common_CGroup_hpp
#define CF_Common_CGroup_hpp

////////////////////////////////////////////////////////////////////////////////

#include "Common/Component.hpp"

namespace CF {
namespace Common {

////////////////////////////////////////////////////////////////////////////////

  /// Component class for tree root
  /// @author Tiago Quintino
  class Common_API CGroup : public Component {

  public:

    /// Contructor
    /// @param name of the component
    CGroup ( const CName& name );

    /// Virtual destructor
    virtual ~CGroup();

    /// Get the class name
    static std::string getClassName () { return "CGroup"; }

  private:

  };

////////////////////////////////////////////////////////////////////////////////

} // Common
} // CF

////////////////////////////////////////////////////////////////////////////////

#endif // CF_Common_CGroup_hpp
