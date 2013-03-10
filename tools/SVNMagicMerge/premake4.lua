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

-- Configuration for module: SVNMagicMerge

project( "SVNMagicMerge" )
location( os.getenv( "PM4OUTPUTDIR" ) )
configuration( { "WIN32" } )
kind( "WindowedApp" )
configuration( { "NOT WIN32" } )
  kind( "ConsoleApp" )
links( { "ArchiveDiffLib", "gucefCORE", "gucefMT", "gucefPATCHER" } )
links( { "ArchiveDiffLib", "gucefCORE", "gucefMT", "gucefPATCHER" } )


configuration( {} )
vpaths { ["Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
files( {
  "src/SVNMagicMerge_main.cpp"
 } )


configuration( {} )
includedirs( { "../../common/include", "../../gucefCOM/include", "../../gucefCOMCORE/include", "../../gucefCORE/include", "../../gucefMT/include", "../../gucefPATCHER/include", "../ArchiveDiffLib/include" } )

configuration( { "ANDROID" } )
includedirs( { "../../gucefCORE/include/android" } )

configuration( { "LINUX" } )
includedirs( { "../../gucefCORE/include/linux" } )

configuration( { "WIN32" } )
includedirs( { "../../gucefCORE/include/mswin" } )

configuration( { "WIN64" } )
includedirs( { "../../gucefCORE/include/mswin" } )
