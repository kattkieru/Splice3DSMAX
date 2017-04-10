#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Euler.h'" )
#endif

////////////////////////////////////////////////////////////////
// THIS FILE IS AUTOMATICALLY GENERATED -- DO NOT MODIFY!!
////////////////////////////////////////////////////////////////
// Generated by kl2edk version 2.6.0
////////////////////////////////////////////////////////////////

#include <FabricEDK.h>
#if FABRIC_EDK_VERSION_MAJ != 2 || FABRIC_EDK_VERSION_MIN != 6
# error "This file needs to be rebuilt for the current EDK version!"
#endif

// Core\Clients\CAPI\KL2EDK.cpp:803
#include "global.h"
// Core\Clients\CAPI\KL2EDK.cpp:855
#include "RotationOrder.h"

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Euler'
// Defined at Euler.kl:22:1

struct Euler
{
  typedef Euler &Result;
  typedef Euler const &INParam;
  typedef Euler &IOParam;
  typedef Euler &OUTParam;
  
  ::Fabric::EDK::KL::Float32 x;
  ::Fabric::EDK::KL::Float32 y;
  ::Fabric::EDK::KL::Float32 z;
  ::Fabric::EDK::KL::RotationOrder ro;
};

inline void Traits<Euler>::ConstructEmpty( Euler &val )
{
  Traits< ::Fabric::EDK::KL::Float32 >::ConstructEmpty( val.x );
  Traits< ::Fabric::EDK::KL::Float32 >::ConstructEmpty( val.y );
  Traits< ::Fabric::EDK::KL::Float32 >::ConstructEmpty( val.z );
  Traits< ::Fabric::EDK::KL::RotationOrder >::ConstructEmpty( val.ro );
}
inline void Traits<Euler>::ConstructCopy( Euler &lhs, Euler const &rhs )
{
  Traits< ::Fabric::EDK::KL::Float32 >::ConstructCopy( lhs.x, rhs.x );
  Traits< ::Fabric::EDK::KL::Float32 >::ConstructCopy( lhs.y, rhs.y );
  Traits< ::Fabric::EDK::KL::Float32 >::ConstructCopy( lhs.z, rhs.z );
  Traits< ::Fabric::EDK::KL::RotationOrder >::ConstructCopy( lhs.ro, rhs.ro );
}
inline void Traits<Euler>::AssignCopy( Euler &lhs, Euler const &rhs )
{
  Traits< ::Fabric::EDK::KL::Float32 >::AssignCopy( lhs.x, rhs.x );
  Traits< ::Fabric::EDK::KL::Float32 >::AssignCopy( lhs.y, rhs.y );
  Traits< ::Fabric::EDK::KL::Float32 >::AssignCopy( lhs.z, rhs.z );
  Traits< ::Fabric::EDK::KL::RotationOrder >::AssignCopy( lhs.ro, rhs.ro );
}
inline void Traits<Euler>::Destruct( Euler &val )
{
  Traits< ::Fabric::EDK::KL::RotationOrder >::Destruct( val.ro );
  Traits< ::Fabric::EDK::KL::Float32 >::Destruct( val.z );
  Traits< ::Fabric::EDK::KL::Float32 >::Destruct( val.y );
  Traits< ::Fabric::EDK::KL::Float32 >::Destruct( val.x );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


