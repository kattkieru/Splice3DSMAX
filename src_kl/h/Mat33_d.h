#ifndef __KL2EDK_AUTOGEN_Mat33_d__
#define __KL2EDK_AUTOGEN_Mat33_d__

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Mat33_d.h'" )
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
#include "Vec3_d.h"

namespace Fabric { namespace EDK { namespace KL {

// KL struct 'Mat33_d'
// Defined at Mat33_d.kl:54:1

struct Mat33_d
{
  typedef Mat33_d &Result;
  typedef Mat33_d const &INParam;
  typedef Mat33_d &IOParam;
  typedef Mat33_d &OUTParam;
  
  Vec3_d row0;
  Vec3_d row1;
  Vec3_d row2;
};

inline void Traits<Mat33_d>::ConstructEmpty( Mat33_d &val )
{
  Traits< Vec3_d >::ConstructEmpty( val.row0 );
  Traits< Vec3_d >::ConstructEmpty( val.row1 );
  Traits< Vec3_d >::ConstructEmpty( val.row2 );
}
inline void Traits<Mat33_d>::ConstructCopy( Mat33_d &lhs, Mat33_d const &rhs )
{
  Traits< Vec3_d >::ConstructCopy( lhs.row0, rhs.row0 );
  Traits< Vec3_d >::ConstructCopy( lhs.row1, rhs.row1 );
  Traits< Vec3_d >::ConstructCopy( lhs.row2, rhs.row2 );
}
inline void Traits<Mat33_d>::AssignCopy( Mat33_d &lhs, Mat33_d const &rhs )
{
  Traits< Vec3_d >::AssignCopy( lhs.row0, rhs.row0 );
  Traits< Vec3_d >::AssignCopy( lhs.row1, rhs.row1 );
  Traits< Vec3_d >::AssignCopy( lhs.row2, rhs.row2 );
}
inline void Traits<Mat33_d>::Destruct( Mat33_d &val )
{
  Traits< Vec3_d >::Destruct( val.row2 );
  Traits< Vec3_d >::Destruct( val.row1 );
  Traits< Vec3_d >::Destruct( val.row0 );
}
}}}

#endif // __KL2EDK_AUTOGEN_Mat33_d__
