#ifndef __KL2EDK_AUTOGEN_Vec3_i__
#define __KL2EDK_AUTOGEN_Vec3_i__

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Vec3_i.h'" )
#endif

////////////////////////////////////////////////////////////////
// THIS FILE IS AUTOMATICALLY GENERATED -- DO NOT MODIFY!!
////////////////////////////////////////////////////////////////
// Generated by kl2edk version 2.3.0
////////////////////////////////////////////////////////////////

#include <FabricEDK.h>
#if FABRIC_EDK_VERSION_MAJ != 2 || FABRIC_EDK_VERSION_MIN != 3
# error "This file needs to be rebuilt for the current EDK version!"
#endif

#include "global.h"

namespace Fabric { namespace EDK { namespace KL {

// KL struct 'Vec3_i'
// Defined at Vec3_i.kl:21:1

struct Vec3_i
{
  typedef Vec3_i &Result;
  typedef Vec3_i const &INParam;
  typedef Vec3_i &IOParam;
  typedef Vec3_i &OUTParam;
  
  SInt32 x;
  SInt32 y;
  SInt32 z;
};

inline void Traits<Vec3_i>::ConstructEmpty( Vec3_i &val )
{
  Traits< SInt32 >::ConstructEmpty( val.x );
  Traits< SInt32 >::ConstructEmpty( val.y );
  Traits< SInt32 >::ConstructEmpty( val.z );
}
inline void Traits<Vec3_i>::ConstructCopy( Vec3_i &lhs, Vec3_i const &rhs )
{
  Traits< SInt32 >::ConstructCopy( lhs.x, rhs.x );
  Traits< SInt32 >::ConstructCopy( lhs.y, rhs.y );
  Traits< SInt32 >::ConstructCopy( lhs.z, rhs.z );
}
inline void Traits<Vec3_i>::AssignCopy( Vec3_i &lhs, Vec3_i const &rhs )
{
  Traits< SInt32 >::AssignCopy( lhs.x, rhs.x );
  Traits< SInt32 >::AssignCopy( lhs.y, rhs.y );
  Traits< SInt32 >::AssignCopy( lhs.z, rhs.z );
}
inline void Traits<Vec3_i>::Destruct( Vec3_i &val )
{
  Traits< SInt32 >::Destruct( val.z );
  Traits< SInt32 >::Destruct( val.y );
  Traits< SInt32 >::Destruct( val.x );
}
}}}

#endif // __KL2EDK_AUTOGEN_Vec3_i__