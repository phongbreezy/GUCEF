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

-- Configuration for module: gucefDRN_TestApp

project( "gucefDRN_TestApp" )
location( os.getenv( "PM4OUTPUTDIR" ) )
configuration( { "WIN32" } )
kind( "WindowedApp" )
configuration( { "NOT WIN32" } )
  kind( "ConsoleApp" )
links( { "gucefCOMCORE", "gucefCORE", "gucefDRN", "gucefMT" } )
links( { "gucefCOMCORE", "gucefCORE", "gucefDRN", "gucefMT" } )


configuration( {} )
vpaths { ["Headers"] = { "**.h", "**.hpp", "**.hxx" } }
files( {
  "include/TestCode_PeerToPeer.h"
 } )



configuration( {} )
vpaths { ["Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
files( {
  "src/gucefDRN_TestApp.cpp",
  "src/TestCode_PeerToPeer.cpp"
 } )


configuration( {} )
includedirs( { "../../common/include", "../../gucefCOMCORE/include", "../../gucefCORE/include", "../../gucefDRN/include", "../../gucefMT/include", "include" } )

configuration( { "ANDROID" } )
includedirs( { "../../gucefCORE/include/android" } )

configuration( { "LINUX" } )
includedirs( { "../../gucefCORE/include/linux" } )

configuration( { "WIN32" } )
includedirs( { "../../gucefCOMCORE/include/mswin", "../../gucefCORE/include/mswin" } )

configuration( { "WIN64" } )
includedirs( { "../../gucefCOMCORE/include/mswin", "../../gucefCORE/include/mswin" } )
