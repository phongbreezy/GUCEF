/*
 *  ProjectGenerator: Tool to generate module/project files
 *  Copyright (C) 2002 - 2011.  Dinand Vanvelzen
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

#include <stdio.h>

#ifndef GUCEF_CORE_LOGGING_H
#include "gucefCORE_Logging.h"
#define GUCEF_CORE_LOGGING_H
#endif /* GUCEF_CORE_LOGGING_H ? */

#ifndef GUCEF_CORE_DVCPPOSWRAP_H
#include "DVCPPOSWRAP.h"
#define GUCEF_CORE_DVCPPOSWRAP_H
#endif /* GUCEF_CORE_DVCPPOSWRAP_H ? */

#ifndef GUCEF_CORE_CFILEACCESS_H
#include "CFileAccess.h"
#define GUCEF_CORE_CFILEACCESS_H
#endif /* GUCEF_CORE_CFILEACCESS_H ? */

#ifndef GUCEF_CORE_CONFIGSTORE_H
#include "CConfigStore.h"
#define GUCEF_CORE_CONFIGSTORE_H
#endif /* GUCEF_CORE_CONFIGSTORE_H ? */

#ifndef GUCEF_PROJECTGEN_DATATYPES_H
#include "gucefProjectGen_DataTypes.h"
#define GUCEF_PROJECTGEN_DATATYPES_H
#endif /* GUCEF_PROJECTGEN_DATATYPES_H ? */

#ifndef GUCEF_PROJECTGEN_CIPROJECTGENERATOR_H
#include "gucefProjectGen_CIProjectGenerator.h"
#define GUCEF_PROJECTGEN_CIPROJECTGENERATOR_H
#endif /* GUCEF_PROJECTGEN_CIPROJECTGENERATOR_H ? */

#ifndef GUCEF_PROJECTGEN_CIPROJECTINFOGATHERER_H
#include "gucefProjectGen_CIProjectInfoGatherer.h"
#define GUCEF_PROJECTGEN_CIPROJECTINFOGATHERER_H
#endif /* GUCEF_PROJECTGEN_CIPROJECTINFOGATHERER_H ? */

#ifndef GUCEF_PROJECTGEN_CDIRCRAWLINGPROJECTINFOGATHERER_H
#include "gucefProjectGen_CDirCrawlingProjectInfoGatherer.h"
#define GUCEF_PROJECTGEN_CDIRCRAWLINGPROJECTINFOGATHERER_H
#endif /* GUCEF_PROJECTGEN_CDIRCRAWLINGPROJECTINFOGATHERER_H ? */

#ifndef GUCEF_PROJECTGEN_CXMLPROJECTGENERATOR_H
#include "gucefProjectGen_CXmlProjectGenerator.h"
#define GUCEF_PROJECTGEN_CXMLPROJECTGENERATOR_H
#endif /* GUCEF_PROJECTGEN_CXMLPROJECTGENERATOR_H ? */

#ifndef GUCEF_PROJECTGEN_CCMAKEPROJECTGENERATOR_H
#include "gucefProjectGen_CCMakeProjectGenerator.h"
#define GUCEF_PROJECTGEN_CCMAKEPROJECTGENERATOR_H
#endif /* GUCEF_PROJECTGEN_CCMAKEPROJECTGENERATOR_H ? */

#ifndef GUCEF_PROJECTGEN_CANDROIDMAKEFILEGENERATOR_H
#include "gucefProjectGen_CAndroidMakefileGenerator.h"
#define GUCEF_PROJECTGEN_CANDROIDMAKEFILEGENERATOR_H
#endif /* GUCEF_PROJECTGEN_CANDROIDMAKEFILEGENERATOR_H ? */

#ifndef GUCEF_PROJECTGEN_CPREMAKE4PROJECTGENERATOR_H
#include "gucefProjectGen_CPremake4ProjectGenerator.h"
#define GUCEF_PROJECTGEN_CPREMAKE4PROJECTGENERATOR_H
#endif /* GUCEF_PROJECTGEN_CPREMAKE4PROJECTGENERATOR_H ? */

#ifndef GUCEF_PROJECTGEN_CPROJECTGENGLOBAL_H
#include "gucefProjectGen_CProjectGenGlobal.h"
#define GUCEF_PROJECTGEN_CPROJECTGENGLOBAL_H
#endif /* GUCEF_PROJECTGEN_CPROJECTGENGLOBAL_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

using namespace GUCEF;
using namespace GUCEF::PROJECTGEN;

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

bool
LoadConfig( void )
{GUCEF_TRACE;

    const CORE::CString configFile = "ProjectGenerator.ini";

    CORE::CString configFilePath = CORE::CombinePath( "$MODULEDIR$", configFile );
    configFilePath = CORE::RelativePath( configFilePath );

    if ( !CORE::FileExists( configFilePath ) )
    {
        configFilePath = CORE::CombinePath( "$CURWORKDIR$", configFile );
        configFilePath = CORE::RelativePath( configFilePath );

        if ( !FileExists( configFilePath ) )
        {
            return false;
        }
    }

    CORE::CConfigStore& configStore = CORE::CCoreGlobal::Instance()->GetConfigStore();
    configStore.SetConfigFile( configFilePath );
    return configStore.LoadConfig();
}

/*-------------------------------------------------------------------------*/

void
ParseParams( const int argc                 ,
             char* argv[]                   ,
             CORE::CValueList& keyValueList )
{GUCEF_TRACE;

    keyValueList.DeleteAll();
    GUCEF::CORE::CString argString;
    if ( argc > 0 )
    {
        argString = *argv;

        // Combine the argument strings back into a single string because we don't want to use
        // a space as the seperator
        for ( int i=1; i<argc; ++i )
        {
            argString += ' ' + CORE::CString( argv[ i ] );
        }

        // Parse the param list based on the ' symbol
        GUCEF_LOG( CORE::LOGLEVEL_NORMAL, "Application parameters: " + argString );
        keyValueList.SetMultiple( argString, '*' );
    }
}

/*---------------------------------------------------------------------------*/

/*
 *      Application entry point
 */
GUCEF_OSMAIN_BEGIN
{GUCEF_TRACE;

    GUCEF_LOG( CORE::LOGLEVEL_NORMAL, "This tool was compiled on: " __DATE__ " @ " __TIME__ );

    CORE::CCoreGlobal::Instance();
    PROJECTGEN::CProjectGenGlobal::Instance();
    
    CORE::CValueList keyValueList;
    ParseParams( argc, argv, keyValueList );

    // Support overriding environment variables from a file.
    // This can be important for build environments which rely on such variables 
    CORE::CString envOverrideFile = keyValueList.GetValueAlways( "envOverridesFile" );
    if ( !envOverrideFile.IsNULLOrEmpty() )
    {
        CORE::CString fileContent;
        if ( CORE::LoadTextFileAsString( envOverrideFile, fileContent, true, "\n" ) )
        {
            CORE::SetEnvOverrides( fileContent );
        }
    }

    CORE::CString outputDir = keyValueList.GetValueAlways( "outputDir" );
    if ( outputDir.IsNULLOrEmpty() )
    {
        outputDir = CORE::RelativePath( "$CURWORKDIR$" );
    }

    CORE::CString logFilename = outputDir;
    CORE::AppendToPath( logFilename, "ProjectGenerator_Log.txt" );

    keyValueList.Set( "logfile", logFilename );

    CORE::CFileAccess logFileAccess( logFilename, "w" );
    CORE::CStdLogger logger( logFileAccess );
    CORE::CCoreGlobal::Instance()->GetLogManager().AddLogger( &logger );

    CORE::CPlatformNativeConsoleLogger console;
    CORE::CCoreGlobal::Instance()->GetLogManager().AddLogger( console.GetLogger() );
    
    CORE::CCoreGlobal::Instance()->GetLogManager().FlushBootstrapLogEntriesToLogs();

    LoadConfig();

    TStringVector rootDirs;
    try
    {
        rootDirs = keyValueList.GetValueVector( "rootDir" );
        GUCEF_LOG( CORE::LOGLEVEL_NORMAL, "Number of rootDir arguments passed from command line: " + CORE::UInt32ToString( rootDirs.size() ) );
    }
    catch ( CORE::CValueList::EUnknownKey& )
    {
        rootDirs.push_back( CORE::RelativePath( "$CURWORKDIR$" ) );
        GUCEF_LOG( CORE::LOGLEVEL_NORMAL, "Using current working directory since no rootDir arguments where passed from the command line" );
    }

    bool addToolCompileTimeToOutput = CORE::StringToBool( keyValueList.GetValueAlways( "addToolCompileTimeToOutput" ) );

    // Get the generators to use
    TStringVector generatorList = keyValueList.GetValueAlways( "generators" ).ParseElements( ';', false );
    if ( generatorList.size() == 0  )
    {
        // No specific generators where specified, defaulting...
        generatorList.push_back( "xml" );
    }

    // Set any global dir excludes that where passed as cmd parameters
    TProjectInfo projectInfo;
    projectInfo.globalDirExcludeList = keyValueList.GetValueAlways( "dirsToIgnore" ).ParseElements( ';', false );
    GUCEF_LOG( CORE::LOGLEVEL_NORMAL, "There are " + CORE::UInt32ToString( projectInfo.globalDirExcludeList.size() ) + " dirs in the global dir ignore list" );

    projectInfo.projectName = keyValueList.GetValueAlways( "projectName" );

    // Use an info gatherer to get all the project information for us
    CDirCrawlingProjectInfoGatherer infoGatherer;
    infoGatherer.GatherInfo( rootDirs    ,
                             projectInfo );

    // Now we output the project info using all generators specified
    TStringVector::iterator i = generatorList.begin();
    while ( i != generatorList.end() )
    {
        if ( (*i).Lowercase() == "xml" )
        {
            CXmlProjectGenerator xmlGenerator;
            xmlGenerator.GenerateProject( projectInfo                ,
                                          outputDir                  ,
                                          addToolCompileTimeToOutput ,
                                          keyValueList               );
        }
        else
        if ( (*i).Lowercase() == "androidmake" )
        {
            CAndroidMakefileGenerator androidMakefileGenerator;
            androidMakefileGenerator.GenerateProject( projectInfo                ,
                                                      outputDir                  ,
                                                      addToolCompileTimeToOutput ,
                                                      keyValueList               );
        }
        else
        if ( (*i).Lowercase() == "cmake" )
        {
            CCMakeProjectGenerator cmakeGenerator;
            cmakeGenerator.GenerateProject( projectInfo                ,
                                            outputDir                  ,
                                            addToolCompileTimeToOutput ,
                                            keyValueList               );
        }
        else
        if ( (*i).Lowercase() == "premake4" )
        {
            CPremake4ProjectGenerator premake4Generator;
            premake4Generator.GenerateProject( projectInfo                ,
                                               outputDir                  ,
                                               addToolCompileTimeToOutput ,
                                               keyValueList               );
        }
        ++i;
    }

    GUCEF_LOG( CORE::LOGLEVEL_NORMAL, "Wrote log file to: " + logFilename );

    CORE::CCoreGlobal::Instance()->GetLogManager().ClearLoggers();
    return 0;
}
GUCEF_OSMAIN_END

/*-------------------------------------------------------------------------//
//                                                                         //
//      Info & Changes                                                     //
//                                                                         //
//-------------------------------------------------------------------------//

- 27-11-2004 :
        - Dinand: Initial implementation

---------------------------------------------------------------------------*/
