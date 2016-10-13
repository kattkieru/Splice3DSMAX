#ifndef __KL2EDK_AUTOGEN_Complex__
#define __KL2EDK_AUTOGEN_Complex__

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Complex.h'" )
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

namespace Fabric { namespace EDK { namespace KL {

// KL struct 'Complex'
// Defined at Complex.kl:17:1

struct Complex
{
  typedef Complex &Result;
  typedef Complex const &INParam;
  typedef Complex &IOParam;
  typedef Complex &OUTParam;
  
  Float32 re;
  Float32 im;
};

inline void Traits<Complex>::ConstructEmpty( Complex &val )
{
  Traits< Float32 >::ConstructEmpty( val.re );
  Traits< Float32 >::ConstructEmpty( val.im );
}
inline void Traits<Complex>::ConstructCopy( Complex &lhs, Complex const &rhs )
{
  Traits< Float32 >::ConstructCopy( lhs.re, rhs.re );
  Traits< Float32 >::ConstructCopy( lhs.im, rhs.im );
}
inline void Traits<Complex>::AssignCopy( Complex &lhs, Complex const &rhs )
{
  Traits< Float32 >::AssignCopy( lhs.re, rhs.re );
  Traits< Float32 >::AssignCopy( lhs.im, rhs.im );
}
inline void Traits<Complex>::Destruct( Complex &val )
{
  Traits< Float32 >::Destruct( val.im );
  Traits< Float32 >::Destruct( val.re );
}
}}}

#endif // __KL2EDK_AUTOGEN_Complex__
