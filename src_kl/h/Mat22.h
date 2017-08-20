#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Mat22.h'" )
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
#include "Vec2.h"

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Mat22'
// Defined at Mat22.kl:21:1

struct Mat22
{
  typedef Mat22 &Result;
  typedef Mat22 const &INParam;
  typedef Mat22 &IOParam;
  typedef Mat22 &OUTParam;
  
  ::Fabric::EDK::KL::Vec2 row0;
  ::Fabric::EDK::KL::Vec2 row1;
};

inline void Traits<Mat22>::ConstructEmpty( Mat22 &val )
{
  Traits< ::Fabric::EDK::KL::Vec2 >::ConstructEmpty( val.row0 );
  Traits< ::Fabric::EDK::KL::Vec2 >::ConstructEmpty( val.row1 );
}
inline void Traits<Mat22>::ConstructCopy( Mat22 &lhs, Mat22 const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec2 >::ConstructCopy( lhs.row0, rhs.row0 );
  Traits< ::Fabric::EDK::KL::Vec2 >::ConstructCopy( lhs.row1, rhs.row1 );
}
inline void Traits<Mat22>::AssignCopy( Mat22 &lhs, Mat22 const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec2 >::AssignCopy( lhs.row0, rhs.row0 );
  Traits< ::Fabric::EDK::KL::Vec2 >::AssignCopy( lhs.row1, rhs.row1 );
}
inline void Traits<Mat22>::Destruct( Mat22 &val )
{
  Traits< ::Fabric::EDK::KL::Vec2 >::Destruct( val.row1 );
  Traits< ::Fabric::EDK::KL::Vec2 >::Destruct( val.row0 );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


