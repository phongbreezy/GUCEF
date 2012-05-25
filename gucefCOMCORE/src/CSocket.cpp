/*
 *  gucefCOMCORE: GUCEF module providing basic communication facilities
 *  Copyright (C) 2002 - 2007.  Dinand Vanvelzen
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#include <string.h>               /* string utils */

#include "CSocket.h"              /* header for this class */

#ifndef DVSTRUTILS_H
#include "dvstrutils.h"
#define DVSTRUTILS_H
#endif /* DVSTRUTILS_H ? */

#ifndef GUCEF_CORE_CLOGMANAGER_H
#include "CLogManager.h"              /* we want the log manager for its defines */
#define GUCEF_CORE_CLOGMANAGER_H
#endif /* GUCEF_CORE_CLOGMANAGER_H ? */

#ifndef GUCEF_CORE_DVCPPSTRINGUTILS_H
#include "dvcppstringutils.h"
#define GUCEF_CORE_DVCPPSTRINGUTILS_H
#endif /* GUCEF_CORE_DVCPPSTRINGUTILS_H ? */

#ifndef GUCEF_COMCORE_DVSOCKET_H
#include "dvwinsock.h"
#define GUCEF_COMCORE_DVSOCKET_H
#endif /* GUCEF_COMCORE_DVSOCKET_H ? */

#ifndef CCOM_H
#include "CCom.h"		  /* network manager */
#define CCOM_H
#endif /* CCOM_H ? */

#ifndef GUCEF_COMCORE_CCOMCOREGLOBAL_H
#include "gucefCOMCORE_CComCoreGlobal.h"
#define GUCEF_COMCORE_CCOMCOREGLOBAL_H
#endif /* GUCEF_COMCORE_CCOMCOREGLOBAL_H ? */

#if ( GUCEF_PLATFORM == GUCEF_PLATFORM_MSWIN )

  #undef FD_SETSIZE
  #define FD_SETSIZE 1      /* should set the size of the FD set struct to 1 for VC */
  #include <winsock2.h>
  #include <Ws2tcpip.h>
  #include <Wspiapi.h>

#elif ( ( GUCEF_PLATFORM == GUCEF_PLATFORM_LINUX ) || ( GUCEF_PLATFORM == GUCEF_PLATFORM_ANDROID ) )

  #include <unistd.h>
  #include <sys/socket.h>
  #include <sys/types.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>

#endif

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace COMCORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

CSocket::CSocket( void )
{GUCEF_TRACE;

        /*
         *      Register the socket object so that it's capable of
         *      receiving update events.
         */
        CComCoreGlobal::Instance()->GetCom().RegisterSocketObject( this );
}

/*-------------------------------------------------------------------------*/

CSocket::~CSocket()
{GUCEF_TRACE;

        /*
         *      Unregister the socket object so that it's removed
         *      from the update event notification list
         */
        CComCoreGlobal::Instance()->GetCom().UnregisterSocketObject( this );
}

/*-------------------------------------------------------------------------*/

void
CSocket::SetSocketID( UInt32 sid )
{GUCEF_TRACE;
        _sid = sid;
}

/*-------------------------------------------------------------------------*/

UInt32
CSocket::GetSocketID( void ) const
{GUCEF_TRACE;

        return _sid;
}

/*-------------------------------------------------------------------------*/

bool
CSocket::ConvertToIPAddress( const CORE::CString& destaddrstr ,
                             const UInt16 destport            ,
                             CIPAddress& resolvedDest         )
{GUCEF_TRACE;

    if ( CORE::Check_If_IP( destaddrstr.C_String() ) )
    {
        resolvedDest.SetAddress( inet_addr( destaddrstr.C_String() ) );
        if ( resolvedDest.GetAddress() == INADDR_NONE ) return false;
        resolvedDest.SetPort( destport );
        return true;
    }
    else
    {
        #if 1

        int errorCode = 0;
        struct hostent* retval = dvsocket_gethostbyname( destaddrstr.C_String(), &errorCode );
        if ( retval != NULL )
        {
            GUCEF_DEBUG_LOG( 1, CORE::CString( "CSocket::ConvertToIPAddress(): gethostbyname(): full name: " ) + retval->h_name );
            char* addrStr = inet_ntoa( *( struct ::in_addr*)( retval->h_addr_list[0] ) );
            Int32 netaddr = inet_addr( addrStr );
            if ( netaddr >= 0 )
            {
                resolvedDest.SetAddress( netaddr );
                resolvedDest.SetPort( destport );
                return true;
            }
        }
        return false;

        #else

        /* Alternate method */

        struct addrinfo* info = NULL;
        CORE::CString portString( CORE::Int32ToString( destport ) );
        int retval = getaddrinfo( destaddrstr.C_String() ,
                                  portString.C_String()  ,
                                  NULL                   ,
                                  &info                  );
        if ( retval == 0 )
        {
            struct in_addr* addr = (struct in_addr*)info->ai_addr;
            DEBUGOUTPUTssss( "CSocket::ConvertToIPAddress(): resolved DNS name ", destaddrstr.C_String(), " to ", inet_ntoa( *addr ) );
            resolvedDest.netaddr = inet_addr( inet_ntoa( *addr ) ); // <- does this actually work ???
            resolvedDest.port = htons( destport );
            return true;
        }
        #ifdef GUCEF_COMCORE_DEBUG_MODE
        DEBUGOUTPUTsi( "CSocket::ConvertToIPAddress(): gethostbyname() failed with code ", retval );
        #endif
        return false;

        #endif
    }
}

/*-------------------------------------------------------------------------*/

bool
CSocket::ConvertFromIPAddress( const CIPAddress& src     ,
                               CORE::CString& srcaddrstr ,
                               UInt16& srcport           )
{GUCEF_TRACE;

    ::in_addr addrStruct;

    #if ( GUCEF_PLATFORM == GUCEF_PLATFORM_MSWIN )
    addrStruct.S_un.S_addr = src.GetAddress();
    #elif ( ( GUCEF_PLATFORM == GUCEF_PLATFORM_LINUX ) || ( GUCEF_PLATFORM == GUCEF_PLATFORM_ANDROID ) )
    addrStruct.s_addr = src.GetAddress();
    #endif

    const char* addrStr = inet_ntoa( addrStruct );
    if ( addrStr != NULL )
    {
        srcaddrstr = addrStr;
        srcport = ntohs( src.GetPort() );
        return true;
    }
    return false;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace COMCORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
