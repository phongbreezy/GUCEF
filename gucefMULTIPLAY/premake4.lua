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

-- Configuration for module: gucefMULTIPLAY

project( "gucefMULTIPLAY" )
location( os.getenv( "PM4OUTPUTDIR" ) )
kind( "SharedLib" )
links( { "gucefCOM", "gucefCOMCORE", "gucefCORE", "gucefMT" } )
links( { "gucefCOM", "gucefCOMCORE", "gucefCORE", "gucefMT" } )


configuration( {} )
vpaths { ["Headers"] = { "**.h", "**.hpp", "**.hxx" } }
files( {
  "include/gucefMULTIPLAY.h",
  "include/gucefMULTIPLAY_CMultiPlayControl.h",
  "include/gucefMULTIPLAY_config.h",
  "include/gucefMULTIPLAY_CPassiveURLServerListProvider.h",
  "include/gucefMULTIPLAY_CServerList.h",
  "include/gucefMULTIPLAY_CServerListProvider.h",
  "include/gucefMULTIPLAY_DLLInit.h",
  "include/gucefMULTIPLAY_macros.h",
  "include/gucefMULTIPLAY_Types.h"
 } )



configuration( {} )
vpaths { ["Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
files( {
  "src/gucefMULTIPLAY_CMultiPlayControl.cpp",
  "src/gucefMULTIPLAY_CPassiveURLServerListProvider.cpp",
  "src/gucefMULTIPLAY_CServerList.cpp",
  "src/gucefMULTIPLAY_CServerListProvider.cpp"
 } )


configuration( {} )
includedirs( { "../common/include", "../gucefCOM/include", "../gucefCOMCORE/include", "../gucefCORE/include", "../gucefMT/include", "include" } )

configuration( { "ANDROID" } )
includedirs( { "../gucefCORE/include/android" } )

configuration( { "LINUX" } )
includedirs( { "../gucefCORE/include/linux" } )

configuration( { "WIN32" } )
includedirs( { "../gucefCOMCORE/include/mswin", "../gucefCORE/include/mswin" } )

configuration( { "WIN64" } )
includedirs( { "../gucefCOMCORE/include/mswin", "../gucefCORE/include/mswin" } )
