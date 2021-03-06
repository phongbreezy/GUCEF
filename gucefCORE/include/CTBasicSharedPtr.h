/*
 *  gucefCORE: GUCEF module providing O/S abstraction and generic solutions
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

#ifndef GUCEF_CORE_CTBASICSHAREDPTR_H
#define GUCEF_CORE_CTBASICSHAREDPTR_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#include <assert.h>

#ifndef GUCEF_CORE_CTDYNAMICDESTRUCTORBASE_H
#include "CTDynamicDestructorBase.h"
#define GUCEF_CORE_CTDYNAMICDESTRUCTORBASE_H
#endif /* GUCEF_CORE_CTDYNAMICDESTRUCTORBASE_H ? */

#ifndef GUCEF_CORE_MACROS_H
#include "gucefCORE_macros.h"       /* module macro's */
#define GUCEF_CORE_MACROS_H
#endif /* GUCEF_CORE_MACROS_H ? */

#include "ExceptionMacros.h"

#ifndef GUCEF_CORE_CTRACER_H
#include "CTracer.h"
#define GUCEF_CORE_CTRACER_H
#endif /* GUCEF_CORE_CTRACER_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      TEMPLATES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

/**
 *  Templated implementation of a shared pointer.
 *
 *  A shared pointer adds some safety to pointers that get passed
 *  around where objects keep a reference to object instances independent
 *  of each other. In such situations it can become unclear who is responsible
 *  for destroying the referenced object instance.
 *  The shared pointer will reference count the pointer and ensure that even
 *  though the original owner has no knowledge of other classes referencing the
 *  object it can safely manage object destruction as desired.
 *
 *  Note that the usage of an external destructor for the shared object by means of the
 *  CTSharedObjectDestructor template is mandatory. By passing in a pointer to such a class
 *  you basically create a callback link for cleanup purposes.
 *
 *  Note that this shared pointer implementation is by no means threadsafe and should
 *  never be used across thread-boundries.
 */
template< typename T >
class CTBasicSharedPtr
{
    public:

    typedef CTDynamicDestructorBase< T >   TDestructor;

    public:

    /**
     *  Constructor that allows you to create an 'uninitialized' pointer.
     *  You will have to assign a valid shared pointer at a later time
     *  to initialize the shared pointer.
     *
     *  Note that if you attempt to use the shared pointer before it
     *  is initialized an exception will be thrown
     *
     */
    CTBasicSharedPtr( void );

    CTBasicSharedPtr( T* ptr                                         ,
                      CTDynamicDestructorBase< T >* objectDestructor );

    // inlined copy constructor, has to be inlined in class definition for now due to VC6 limitations
    template< class Derived >
    CTBasicSharedPtr( const CTBasicSharedPtr< Derived >& src )
        : m_ptr( NULL )              ,
          m_refCounter( NULL )       ,
          m_objectDestructor( NULL )
    {
        InitializeUsingInheritance( src );
    }

    CTBasicSharedPtr( const CTBasicSharedPtr& src );

    virtual ~CTBasicSharedPtr();

    template< class RelatedClass >
    bool InitializeUsingInheritance( const CTBasicSharedPtr< RelatedClass >& classPtr )
    {
        Unlink();

        LockData();

        // The static cast below is performed as a compile time validation
        // of the type passed.
        T* relatedClass = static_cast< T* >( const_cast< RelatedClass* >( classPtr.GetPointerAlways() ) );
        if ( NULL != relatedClass )
        {
            m_ptr = relatedClass;
            m_refCounter = const_cast< UInt32* >( classPtr.GetReferenceCounter() );
            m_objectDestructor = reinterpret_cast< CTBasicSharedPtr< T >::TDestructor* >( classPtr.GetDestructor() );

            ++(*m_refCounter);

            UnlockData();
            return true;
        }
        UnlockData();
        return false;
    }

    // implemented inline as a workaround for VC6 issues
    template< class Derived >
    CTBasicSharedPtr& operator=( const CTBasicSharedPtr< Derived >& src )
    {
        if ( &reinterpret_cast< const CTBasicSharedPtr& >( src ) != this )
        {
            InitializeUsingInheritance( src );
        }
        return *this;
    }

    // implemented inline as a workaround for VC6 issues
    // The dummy param is a VC6 hack for templated member functions
    template< class Derived >
    CTBasicSharedPtr< Derived > StaticCast( bool dummy = true )
    {
            // We use the initialization function of the derived type's
            // shared pointer which will have knowledge of both types.
            CTBasicSharedPtr< Derived > retVal;
            retVal.InitializeUsingInheritance( *this );
            return retVal;
    }

    CTBasicSharedPtr& operator=( const CTBasicSharedPtr& src );

    CTBasicSharedPtr& operator=( int nullValue );

    inline bool operator==( int nullValue ) const;

    inline bool operator==( const void* other ) const;

    inline bool operator==( const CTBasicSharedPtr& other ) const;

    inline bool operator!=( int other ) const;

    inline bool operator!=( const void* other ) const;

    inline bool operator!=( const CTBasicSharedPtr& other ) const;

    inline bool operator<( const CTBasicSharedPtr& other ) const;

    /**
     *  operator that implements '(*mySharedPtr)'
     *
     *  @throws ENotInitialized if the pointer is not initialized
     */
    inline T& operator*( void );

    /**
     *  operator that implements '(*mySharedPtr)'
     *
     *  @throws ENotInitialized if the pointer is not initialized
     */
    inline const T& operator*( void ) const;

    /**
     *  operator that emulates 'myPointer->'
     *
     *  @throws ENotInitialized if the pointer is not initialized
     */
    inline T* operator->( void );

    /**
     *  operator that emulates 'myPointer->'
     *
     *  @throws ENotInitialized if the pointer is not initialized
     */
    inline const T* operator->( void ) const;

    /**
     *  Conversion operator to bool to facilitate easy ! etc checks against the
     *  pointer being NULL as some people like to do versus an explicit NULL == check.
     */
    inline operator bool() const;

    inline T* GetPointer( void );

    inline const T* GetPointer( void ) const;

    inline T* GetPointerAlways( void );

    inline const T* GetPointerAlways( void ) const;

    inline bool IsNULL( void ) const;

    UInt32 GetReferenceCount( void ) const;

    const UInt32* GetReferenceCounter( void ) const;

    TDestructor* GetDestructor( void ) const;

    GUCEF_DEFINE_INLINED_MSGEXCEPTION( ENotInitialized );

    protected:

    /**
     *  Can be used by descending classes to implement in-scope memory management
     *  utilizing method 1 as described above.
     */
    void SetToNULL( void );

    /**
     *  Can be used be decending implementations for late initialization.
     */
    void Initialize( T* ptr                        ,
                     TDestructor* objectDestructor );

    /**
     *  Simply sets the object destructor pointer overwriting whatever
     *  the values used to be.
     *  The pointer has to be valid.
     */
    void OverrideDestructor( TDestructor* newObjectDestructor );

    UInt32* GetReferenceCounter( void );

    void Unlink( void );

    /**
     *  no-op in the default implementation.
     *  derived classes wishing to make the shared pointer thread safe
     *  should add a synchronization mechanic in a derived implementation
     *
     *  This function should be implemented to be logically const
     */
    virtual void LockData( void ) const;

    /**
     *  no-op in the default implementation.
     *  derived classes wishing to make the shared pointer thread safe
     *  should add a synchronization mechanic in a derived implementation
     *
     *  This function should be implemented to be logically const
     */
    virtual void UnlockData( void ) const;

    private:

    T* m_ptr;                        /**< the pointer that we wish to reference count */
    UInt32* m_refCounter;            /**< shared reference counter */
    TDestructor* m_objectDestructor; /**< manditory external object destructor */
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

template< typename T >
CTBasicSharedPtr< T >::CTBasicSharedPtr( void )
        : m_ptr( NULL )                          ,
          m_refCounter( NULL )                   ,
          m_objectDestructor( NULL )
{GUCEF_TRACE;

    // Note that if this constructor is used an assignment is required at
    // a later time to initialize the shared pointer
}

/*-------------------------------------------------------------------------*/

template< typename T >
CTBasicSharedPtr< T >::CTBasicSharedPtr( T* ptr                        ,
                                         TDestructor* objectDestructor )
        : m_ptr( ptr )                           ,
          m_refCounter( NULL )                   ,
          m_objectDestructor( objectDestructor )
{GUCEF_TRACE;

    if ( ptr )
    {
        m_refCounter = new UInt32( 1UL );
    }
}

/*-------------------------------------------------------------------------*/

template< typename T >
CTBasicSharedPtr< T >::CTBasicSharedPtr( const CTBasicSharedPtr< T >& src )
        : m_ptr( src.m_ptr )                           ,
          m_refCounter( src.m_refCounter )             ,
          m_objectDestructor( src.m_objectDestructor )
{GUCEF_TRACE;

    src.LockData();

    if ( m_refCounter )
    {
        ++(*m_refCounter);
    }

    src.UnlockData();
}

/*-------------------------------------------------------------------------*/

template< typename T >
CTBasicSharedPtr< T >::~CTBasicSharedPtr()
{GUCEF_TRACE;

    Unlink();
}

/*-------------------------------------------------------------------------*/

template< typename T >
void
CTBasicSharedPtr< T >::Initialize( T* ptr                        ,
                                   TDestructor* objectDestructor )
{GUCEF_TRACE;

    // If you get an assert here:
    //    You have an error in your decending class: you cannot initialize twice
    assert( m_ptr == GUCEF_NULL );
    assert( m_objectDestructor == GUCEF_NULL );
    assert( m_refCounter == GUCEF_NULL );

    // Just in case we did not hit the asserts above because the code was compiled in release
    // mode without asserts we will still allow the scenario by unlinking first
    Unlink();

    LockData();

    m_ptr = ptr;
    m_refCounter = new UInt32( 1UL );
    m_objectDestructor = objectDestructor;

    UnlockData();
}

/*-------------------------------------------------------------------------*/

template< typename T >
void
CTBasicSharedPtr< T >::OverrideDestructor( TDestructor* newObjectDestructor )
{GUCEF_TRACE;

    m_objectDestructor = newObjectDestructor;
}

/*-------------------------------------------------------------------------*/

template< typename T >
typename CTBasicSharedPtr< T >::TDestructor*
CTBasicSharedPtr< T >::GetDestructor( void ) const
{GUCEF_TRACE;

    return m_objectDestructor;
}

/*-------------------------------------------------------------------------*/

template< typename T >
bool
CTBasicSharedPtr< T >::IsNULL( void ) const
{GUCEF_TRACE;

    return GUCEF_NULL == m_ptr;
}

/*-------------------------------------------------------------------------*/

template< typename T >
UInt32
CTBasicSharedPtr< T >::GetReferenceCount( void ) const
{GUCEF_TRACE;

    if ( m_refCounter )
    {
        return *m_refCounter;
    }
    return 0UL;
}

/*-------------------------------------------------------------------------*/

template< typename T >
CTBasicSharedPtr< T >&
CTBasicSharedPtr< T >::operator=( int nullValue )
{GUCEF_TRACE;

    assert( nullValue == GUCEF_NULL );
    Unlink();
    return *this;
}

/*-------------------------------------------------------------------------*/

template< typename T >
CTBasicSharedPtr< T >&
CTBasicSharedPtr< T >::operator=( const CTBasicSharedPtr< T >& src )
{GUCEF_TRACE;

    if ( this != &src )
    {
        Unlink();

        LockData();

        m_ptr = src.m_ptr;
        m_refCounter = src.m_refCounter;
        m_objectDestructor = src.m_objectDestructor;

        if ( m_refCounter )
        {
            ++(*m_refCounter);
        }

        UnlockData();
    }
    return *this;
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline bool
CTBasicSharedPtr< T >::operator<( const CTBasicSharedPtr< T >& other ) const
{GUCEF_TRACE;

    return m_ptr < other.m_ptr;
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline bool
CTBasicSharedPtr< T >::operator==( const CTBasicSharedPtr< T >& other ) const
{GUCEF_TRACE;

    return m_ptr == other.m_ptr;
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline bool
CTBasicSharedPtr< T >::operator==( const void* other ) const
{GUCEF_TRACE;

    return other == m_ptr;
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline bool
CTBasicSharedPtr< T >::operator==( int other ) const
{GUCEF_TRACE;

    if ( 0 == other ) return GUCEF_NULL == m_ptr;
    if ( sizeof( int ) != sizeof( m_ptr ) ) return false;
    return reinterpret_cast< void* >( other ) == m_ptr;
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline bool
operator==( const T* ptr, const CTBasicSharedPtr< T >& other )
{GUCEF_TRACE;

    return other == ptr;
}

/*-------------------------------------------------------------------------*/

/*
 *  workaround for comparison to NULL, since NULL is a integer by default
 */
template< typename T >
inline bool
operator==( const int ptr, const CTBasicSharedPtr< T >& other )
{GUCEF_TRACE;

    assert( GUCEF_NULL == ptr );
    return static_cast< const T* >( GUCEF_NULL ) == other;
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline bool
CTBasicSharedPtr< T >::operator!=( const CTBasicSharedPtr< T >& other ) const
{GUCEF_TRACE;

    return m_ptr != other.m_ptr;
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline bool
CTBasicSharedPtr< T >::operator!=( int other ) const
{GUCEF_TRACE;

    if ( 0 == other ) return GUCEF_NULL != m_ptr;
    if ( sizeof( int ) != sizeof( m_ptr ) ) return true;
    return reinterpret_cast< void* >( other ) != m_ptr;
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline bool
CTBasicSharedPtr< T >::operator!=( const void* other ) const
{GUCEF_TRACE;

    return other != m_ptr;
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline bool
operator!=( const T* ptr, const CTBasicSharedPtr< T >& other )
{GUCEF_TRACE;

    return other != ptr;
}

/*-------------------------------------------------------------------------*/

/*
 *  workaround for comparison to NULL, since NULL is a integer by default
 */
template< typename T >
inline bool
operator!=( int intPtr, const CTBasicSharedPtr< T >& other )
{GUCEF_TRACE;

    return other != intPtr;
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline T&
CTBasicSharedPtr< T >::operator*( void )
{GUCEF_TRACE;

    if ( m_ptr )
    {
        return *m_ptr;
    }

    // Someone forgot to initialize the shared pointer with an assignment
    GUCEF_EMSGTHROW( ENotInitialized, "CTBasicSharedPtr< T >::operator*( void ): uninitialized pointer usage" );
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline const T&
CTBasicSharedPtr< T >::operator*( void ) const
{GUCEF_TRACE;

    if ( GUCEF_NULL != m_ptr )
    {
        return *m_ptr;
    }

    // Someone forgot to initialize the shared pointer with an assignment
    GUCEF_EMSGTHROW( ENotInitialized, "CTBasicSharedPtr< T >::operator*( void ) const: uninitialized pointer usage" );

}

/*-------------------------------------------------------------------------*/

template< typename T >
inline T*
CTBasicSharedPtr< T >::operator->( void )
{GUCEF_TRACE;

    if ( GUCEF_NULL != m_ptr )
    {
        return m_ptr;
    }

    // Someone forgot to initialize the shared pointer with an assignment
    GUCEF_EMSGTHROW( ENotInitialized, "CTBasicSharedPtr< T >::operator->( void ): uninitialized pointer usage" );
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline const T*
CTBasicSharedPtr< T >::operator->( void ) const
{GUCEF_TRACE;

    if ( GUCEF_NULL != m_ptr )
    {
        return m_ptr;
    }

    // Someone forgot to initialize the shared pointer with an assignment
    GUCEF_EMSGTHROW( ENotInitialized, "CTBasicSharedPtr< T >::operator->( void ) const: uninitialized pointer usage" );
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline
CTBasicSharedPtr< T >::operator bool() const
{
    return GUCEF_NULL != m_ptr;
}

/*-------------------------------------------------------------------------*/

template< typename T >
UInt32*
CTBasicSharedPtr< T >::GetReferenceCounter( void )
{
    return m_refCounter;
}

/*-------------------------------------------------------------------------*/

template< typename T >
const UInt32*
CTBasicSharedPtr< T >::GetReferenceCounter( void ) const
{
    return m_refCounter;
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline T*
CTBasicSharedPtr< T >::GetPointer( void )
{GUCEF_TRACE;

    if ( GUCEF_NULL != m_ptr )
    {
        return m_ptr;
    }

    // Someone forgot to initialize the shared pointer with an assignment
    GUCEF_EMSGTHROW( ENotInitialized, "CTBasicSharedPtr< T >::operator->( void ): uninitialized pointer usage" );
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline const T*
CTBasicSharedPtr< T >::GetPointer( void ) const
{GUCEF_TRACE;

    if ( GUCEF_NULL != m_ptr )
    {
        return m_ptr;
    }

    // Someone forgot to initialize the shared pointer with an assignment
    GUCEF_EMSGTHROW( ENotInitialized, "CTBasicSharedPtr< T >::operator->( void ) const: uninitialized pointer usage" );
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline T*
CTBasicSharedPtr< T >::GetPointerAlways( void )
{
    return m_ptr;
}

/*-------------------------------------------------------------------------*/

template< typename T >
inline const T*
CTBasicSharedPtr< T >::GetPointerAlways( void ) const
{
    return m_ptr;
}

/*-------------------------------------------------------------------------*/

template< typename T >
void
CTBasicSharedPtr< T >::Unlink( void )
{GUCEF_TRACE;

    LockData();

    if ( NULL != m_ptr )
    {
        --(*m_refCounter);
        if ( 0UL == *m_refCounter )
        {
            // We should check if the destructor pointer is not-NULL
            // A descending class may NULL it for its own purposes.
            if ( NULL != m_objectDestructor )
            {
                m_objectDestructor->DestroyObject( m_ptr );
                m_objectDestructor = GUCEF_NULL;
            }

            delete m_refCounter;
            m_refCounter = GUCEF_NULL;

            m_ptr = GUCEF_NULL;
        }
    }

    // this object may not have been the last refrence but we still have to NULL
    // the attributes to allow this object to be re-used
    m_objectDestructor = GUCEF_NULL;
    m_refCounter = GUCEF_NULL;
    m_ptr = GUCEF_NULL;

    UnlockData();
}

/*-------------------------------------------------------------------------*/

template< typename T >
void
CTBasicSharedPtr< T >::SetToNULL( void )
{
    LockData();

    m_objectDestructor = GUCEF_NULL;
    delete m_refCounter;
    m_refCounter = GUCEF_NULL;
    m_ptr = GUCEF_NULL;

    UnlockData();
}

/*-------------------------------------------------------------------------*/

template< typename T >
void
CTBasicSharedPtr< T >::LockData( void ) const
{
    // no-op in the default implementation.
    // derived classes wishing to make the shared pointer thread safe
    // should add a synchronization mechanic in a derived implementation
}

/*-------------------------------------------------------------------------*/

template< typename T >
void
CTBasicSharedPtr< T >::UnlockData( void ) const
{
    // no-op in the default implementation.
    // derived classes wishing to make the shared pointer thread safe
    // should add a synchronization mechanic in a derived implementation
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 14-12-2005 :
        - Dinand: Moved code into this new base class from CTSharedPtr to allow
          some level of shared pointer usage without actually requiring the type
          to be defined. ie you can create a shared pointer with a forward declaration.

-----------------------------------------------------------------------------*/

#endif /* GUCEF_CORE_CTBASICSHAREDPTR_H ? */
