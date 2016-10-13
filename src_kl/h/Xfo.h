#ifndef __KL2EDK_AUTOGEN_Xfo__
#define __KL2EDK_AUTOGEN_Xfo__

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Xfo.h'" )
#endif

////////////////////////////////////////////////////////////////
// THIS FILE IS AUTOMATICALLY GENERATED -- DO NOT MODIFY!!
////////////////////////////////////////////////////////////////
// Generated by kl2edk version 2.4.0
////////////////////////////////////////////////////////////////

#include <FabricEDK.h>
#if FABRIC_EDK_VERSION_MAJ != 2 || FABRIC_EDK_VERSION_MIN != 4
# error "This file needs to be rebuilt for the current EDK version!"
#endif

#include "global.h"
#include "Quat.h"
#include "Vec3.h"

namespace Fabric { namespace EDK { namespace KL {

// KL struct 'Xfo'
// Defined at Xfo.kl:29:1

struct Xfo
{
  typedef Xfo &Result;
  typedef Xfo const &INParam;
  typedef Xfo &IOParam;
  typedef Xfo &OUTParam;
  
  Quat ori;
  Vec3 tr;
  Vec3 sc;
};

inline void Traits<Xfo>::ConstructEmpty( Xfo &val )
{
  Traits< Quat >::ConstructEmpty( val.ori );
  Traits< Vec3 >::ConstructEmpty( val.tr );
  Traits< Vec3 >::ConstructEmpty( val.sc );
}
inline void Traits<Xfo>::ConstructCopy( Xfo &lhs, Xfo const &rhs )
{
  Traits< Quat >::ConstructCopy( lhs.ori, rhs.ori );
  Traits< Vec3 >::ConstructCopy( lhs.tr, rhs.tr );
  Traits< Vec3 >::ConstructCopy( lhs.sc, rhs.sc );
}
inline void Traits<Xfo>::AssignCopy( Xfo &lhs, Xfo const &rhs )
{
  Traits< Quat >::AssignCopy( lhs.ori, rhs.ori );
  Traits< Vec3 >::AssignCopy( lhs.tr, rhs.tr );
  Traits< Vec3 >::AssignCopy( lhs.sc, rhs.sc );
}
inline void Traits<Xfo>::Destruct( Xfo &val )
{
  Traits< Vec3 >::Destruct( val.sc );
  Traits< Vec3 >::Destruct( val.tr );
  Traits< Quat >::Destruct( val.ori );
}
}}}

#endif // __KL2EDK_AUTOGEN_Xfo__
