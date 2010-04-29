#ifndef COOFluiD_Common_ProviderBase_hpp
#define COOFluiD_Common_ProviderBase_hpp

////////////////////////////////////////////////////////////////////////////////

#include "Common/CF.hpp"
#include "Common/NonCopyable.hpp"

#include "Common/CommonAPI.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace CF {
  namespace Common {

////////////////////////////////////////////////////////////////////////////////

/// @brief Base class for provider types
/// @author Dries Kimpe
/// @author Tiago Quintino
class Common_API ProviderBase : public Common::NonCopyable<ProviderBase> {

public: // methods

  /// Constructor
  ProviderBase ();

  /// Virtual destructor
  virtual ~ProviderBase ();

  /// @return the name of this provider
  virtual std::string getProviderName () const = 0;

  /// @return the type of this provider
  virtual std::string getProviderType () const = 0;

}; // end ProviderBase

////////////////////////////////////////////////////////////////////////////////

  } // namespace Common
} // namespace CF

////////////////////////////////////////////////////////////////////////////////

#endif // COOFluiD_Common_ProviderBase_hpp
