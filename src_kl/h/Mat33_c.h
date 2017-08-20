#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Mat33_c.h'" )
#endif

////////////////////////////////////////////////////////////////
// THIS FILE IS AUTOMATICALLY GENERATED -- DO NOT MODIFY!!
////////////////////////////////////////////////////////////////
// Generated by kl2edk version 2.7.0
////////////////////////////////////////////////////////////////

#include <FabricEDK.h>
#if FABRIC_EDK_VERSION_MAJ != 2 || FABRIC_EDK_VERSION_MIN != 7
# error "This file needs to be rebuilt for the current EDK version!"
#endif

// Core\Clients\CAPI\KL2EDK.cpp:812
#include "global.h"
// Core\Clients\CAPI\KL2EDK.cpp:864
#include "Vec3_c.h"
// Core\Clients\CAPI\KL2EDK.cpp:864
#include "Complex.h"

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Mat33_c'
// Defined at Mat33_c.kl:52:1

struct Mat33_c
{
  typedef Mat33_c &Result;
  typedef Mat33_c const &INParam;
  typedef Mat33_c &IOParam;
  typedef Mat33_c &OUTParam;
  
  ::Fabric::EDK::KL::Vec3_c row0;
  ::Fabric::EDK::KL::Vec3_c row1;
  ::Fabric::EDK::KL::Vec3_c row2;
};

inline void Traits<Mat33_c>::ConstructEmpty( Mat33_c &val )
{
  Traits< ::Fabric::EDK::KL::Vec3_c >::ConstructEmpty( val.row0 );
  Traits< ::Fabric::EDK::KL::Vec3_c >::ConstructEmpty( val.row1 );
  Traits< ::Fabric::EDK::KL::Vec3_c >::ConstructEmpty( val.row2 );
}
inline void Traits<Mat33_c>::ConstructCopy( Mat33_c &lhs, Mat33_c const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec3_c >::ConstructCopy( lhs.row0, rhs.row0 );
  Traits< ::Fabric::EDK::KL::Vec3_c >::ConstructCopy( lhs.row1, rhs.row1 );
  Traits< ::Fabric::EDK::KL::Vec3_c >::ConstructCopy( lhs.row2, rhs.row2 );
}
inline void Traits<Mat33_c>::AssignCopy( Mat33_c &lhs, Mat33_c const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec3_c >::AssignCopy( lhs.row0, rhs.row0 );
  Traits< ::Fabric::EDK::KL::Vec3_c >::AssignCopy( lhs.row1, rhs.row1 );
  Traits< ::Fabric::EDK::KL::Vec3_c >::AssignCopy( lhs.row2, rhs.row2 );
}
inline void Traits<Mat33_c>::Destruct( Mat33_c &val )
{
  Traits< ::Fabric::EDK::KL::Vec3_c >::Destruct( val.row2 );
  Traits< ::Fabric::EDK::KL::Vec3_c >::Destruct( val.row1 );
  Traits< ::Fabric::EDK::KL::Vec3_c >::Destruct( val.row0 );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


