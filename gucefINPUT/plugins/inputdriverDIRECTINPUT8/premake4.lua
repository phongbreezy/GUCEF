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

-- Configuration for module: inputdriverDIRECTINPUT8


configuration( { "WIN32" } )
  project( "inputdriverDIRECTINPUT8" )

configuration( { "WIN64" } )
  project( "inputdriverDIRECTINPUT8" )
endif()
location( os.getenv( "PM4OUTPUTDIR" ) )
configuration( { "WIN32" } )
kind( "SharedLib" )
configuration( { "WIN64" } )
kind( "SharedLib" )

configuration( { "WIN32" } )
  links( { "gucefCORE", "gucefINPUT", "gucefMT" } )
  defines( { "BUILD_GUCEF_INPUT_PLUGIN_DLL", "INPUTDRIVERDIRECTINPUT8_BUILD_MODULE" } )

configuration( { "WIN64" } )
  links( { "gucefCORE", "gucefINPUT", "gucefMT" } )
  defines( { "BUILD_GUCEF_INPUT_PLUGIN_DLL", "INPUTDRIVERDIRECTINPUT8_BUILD_MODULE" } )


configuration( { "WIN32" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "include\DLLMainInputDriverDI8.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src\DLLMainInputDriverDI8.cpp"
    } )



configuration( { "WIN64" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "include\DLLMainInputDriverDI8.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src\DLLMainInputDriverDI8.cpp"
    } )


configuration( {} )
includedirs( { "../../../common/include", "../../../gucefCORE/include", "../../../gucefINPUT/include", "../../../gucefMT/include" } )

configuration( { "WIN32" } )
includedirs( { "../../../gucefCORE/include/mswin", "include" } )

configuration( { "WIN64" } )
includedirs( { "../../../gucefCORE/include/mswin", "include" } )
