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

-- Configuration for module: gucefIMAGE_TestApp


project( "gucefIMAGE_TestApp" )
location( os.getenv( "PM4OUTPUTDIR" ) )

configuration( {} )
language( "C++" )

configuration( { "ANDROID" } )
language( "C" )

configuration( { "LINUX" } )
language( "C" )

configuration( { "OSX" } )
language( "C" )

configuration( { "WIN32" } )
language( "C" )

configuration( { "WIN64" } )
language( "C" )

configuration( { "WIN32" } )
kind( "WindowedApp" )
configuration( { "NOT WIN32" } )
  kind( "ConsoleApp" )
links( { "gucefCORE", "gucefIMAGE", "gucefMT" } )
links( { "gucefCORE", "gucefIMAGE", "gucefMT" } )


configuration( {} )
vpaths { ["Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
files( {
  "src/gucefIMAGE_TestApp.cpp"
 } )


configuration( {} )
includedirs( { "../../common/include", "../../gucefCORE/include", "../../gucefIMAGE/include", "../../gucefMT/include" } )

configuration( { "ANDROID" } )
includedirs( { "../../gucefCORE/include/android" } )

configuration( { "LINUX" } )
includedirs( { "../../gucefCORE/include/linux" } )

configuration( { "WIN32" } )
includedirs( { "../../gucefCORE/include/mswin" } )

configuration( { "WIN64" } )
includedirs( { "../../gucefCORE/include/mswin" } )