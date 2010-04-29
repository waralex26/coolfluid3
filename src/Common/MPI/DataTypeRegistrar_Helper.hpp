#ifndef DataTypeREGISTRAR_HELPER_hpp
#define DataTypeREGISTRAR_HELPER_hpp

#include "Common/MPI/DataType.hpp"

namespace CF {
namespace Common  {
namespace MPI {

////////////////////////////////////////////////////////////////////////////////

class DataTypeRegistrar_Helper : public MPI::DataType
{
protected:
    MPI_Datatype TheType;

public:
    DataTypeRegistrar_Helper ();
    virtual ~DataTypeRegistrar_Helper ();


    void DoRegister ();

    MPI_Datatype GetType () const
    { return TheType; }

};

////////////////////////////////////////////////////////////////////////////////

} // MPI
} // Common
} // CF

#endif
