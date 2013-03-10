--------------------------------------------------------------------
-- This file was automatically generated by ProjectGenerator
-- which is tooling part the build system designed for GUCEF
--     (Galaxy Unlimited Framework)
-- For the latest info, see http://www.VanvelzenSoftware.com/
--
-- The contents of this file are placed in the public domain. Feel
-- free to make use of it in any way you like.
--------------------------------------------------------------------
--

-- Configuration for module: inputdriverMSWINMSG


configuration( { "WIN32" } )
  project( "inputdriverMSWINMSG" )

configuration( { "WIN64" } )
  project( "inputdriverMSWINMSG" )
endif()
location( os.getenv( "PM4OUTPUTDIR" ) )
configuration( { "WIN32" } )
kind( "SharedLib" )
configuration( { "WIN64" } )
kind( "SharedLib" )

configuration( { "WIN32" } )
  links( { "gucefCORE", "gucefINPUT", "gucefMT" } )
  defines( { "BUILD_GUCEF_INPUT_PLUGIN_DLL", "INPUTDRIVERMSWINMSG_BUILD_MODULE" } )

configuration( { "WIN64" } )
  links( { "gucefCORE", "gucefINPUT", "gucefMT" } )
  defines( { "BUILD_GUCEF_INPUT_PLUGIN_DLL", "INPUTDRIVERMSWINMSG_BUILD_MODULE" } )


configuration( { "WIN32" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "include\DLLMainInputDriverMSWINMSG.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src\DLLMainInputDriverMSWINMSG.cpp"
    } )



configuration( { "WIN64" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "include\DLLMainInputDriverMSWINMSG.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src\DLLMainInputDriverMSWINMSG.cpp"
    } )


configuration( {} )
includedirs( { "../../../common/include", "../../../gucefCORE/include", "../../../gucefINPUT/include", "../../../gucefMT/include" } )

configuration( { "WIN32" } )
includedirs( { "../../../gucefCORE/include/mswin", "include" } )

configuration( { "WIN64" } )
includedirs( { "../../../gucefCORE/include/mswin", "include" } )
