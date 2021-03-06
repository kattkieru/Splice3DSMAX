#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Vec3_d.h'" )
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

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Vec3_d'
// Defined at Vec3_d.kl:21:1

struct Vec3_d
{
  typedef Vec3_d &Result;
  typedef Vec3_d const &INParam;
  typedef Vec3_d &IOParam;
  typedef Vec3_d &OUTParam;
  
  ::Fabric::EDK::KL::Float64 x;
  ::Fabric::EDK::KL::Float64 y;
  ::Fabric::EDK::KL::Float64 z;
};

inline void Traits<Vec3_d>::ConstructEmpty( Vec3_d &val )
{
  Traits< ::Fabric::EDK::KL::Float64 >::ConstructEmpty( val.x );
  Traits< ::Fabric::EDK::KL::Float64 >::ConstructEmpty( val.y );
  Traits< ::Fabric::EDK::KL::Float64 >::ConstructEmpty( val.z );
}
inline void Traits<Vec3_d>::ConstructCopy( Vec3_d &lhs, Vec3_d const &rhs )
{
  Traits< ::Fabric::EDK::KL::Float64 >::ConstructCopy( lhs.x, rhs.x );
  Traits< ::Fabric::EDK::KL::Float64 >::ConstructCopy( lhs.y, rhs.y );
  Traits< ::Fabric::EDK::KL::Float64 >::ConstructCopy( lhs.z, rhs.z );
}
inline void Traits<Vec3_d>::AssignCopy( Vec3_d &lhs, Vec3_d const &rhs )
{
  Traits< ::Fabric::EDK::KL::Float64 >::AssignCopy( lhs.x, rhs.x );
  Traits< ::Fabric::EDK::KL::Float64 >::AssignCopy( lhs.y, rhs.y );
  Traits< ::Fabric::EDK::KL::Float64 >::AssignCopy( lhs.z, rhs.z );
}
inline void Traits<Vec3_d>::Destruct( Vec3_d &val )
{
  Traits< ::Fabric::EDK::KL::Float64 >::Destruct( val.z );
  Traits< ::Fabric::EDK::KL::Float64 >::Destruct( val.y );
  Traits< ::Fabric::EDK::KL::Float64 >::Destruct( val.x );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


