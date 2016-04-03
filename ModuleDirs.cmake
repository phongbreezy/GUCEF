#-------------------------------------------------------------------
# This file was automatically generated by ProjectGenerator
# which is tooling part the build system designed for GUCEF
#     (Galaxy Unlimited Framework)
# For the latest info, see http://www.VanvelzenSoftware.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------
#
add_subdirectory( apps/gucefPATCHERAPP )
add_subdirectory( apps/gucefPRODMANAPP )
add_subdirectory( dependencies/cegui/cegui )
add_subdirectory( dependencies/cegui/cegui/src/CommonDialogs )
add_subdirectory( dependencies/cegui/cegui/src/RendererModules/Null )
add_subdirectory( dependencies/cegui/cegui/src/RendererModules/Ogre )
add_subdirectory( dependencies/cegui/cegui/src/RendererModules/OpenGL )
add_subdirectory( dependencies/cegui/cegui/src/RendererModules/OpenGLES )
add_subdirectory( dependencies/cegui/cegui/src/ScriptModules/Lua )
add_subdirectory( dependencies/cegui/cegui/src/WindowRendererSets/Core )
add_subdirectory( dependencies/DVPACKSYS )
add_subdirectory( dependencies/FreeImage )
add_subdirectory( dependencies/freetype )
add_subdirectory( dependencies/glew )
add_subdirectory( dependencies/libparsifal )
add_subdirectory( dependencies/libRocket/Source/Controls )
add_subdirectory( dependencies/libRocket/Source/Core )
add_subdirectory( dependencies/libRocket/Source/Debugger )
add_subdirectory( dependencies/miniupnpc )
add_subdirectory( dependencies/MyGui/Common )
add_subdirectory( dependencies/MyGui/Common/Base )
add_subdirectory( dependencies/MyGui/Common/Base/DirectX )
add_subdirectory( dependencies/MyGui/Common/Base/Ogre )
add_subdirectory( dependencies/MyGui/Common/Base/OpenGL )
add_subdirectory( dependencies/MyGui/Common/BaseLayout )
add_subdirectory( dependencies/MyGui/Common/FileSystemInfo )
add_subdirectory( dependencies/MyGui/Common/Input )
add_subdirectory( dependencies/MyGui/Common/Input/OIS )
add_subdirectory( dependencies/MyGui/Common/Input/Win32API )
add_subdirectory( dependencies/MyGui/Common/Input/Win32_OIS )
add_subdirectory( dependencies/MyGui/Common/ItemBox )
add_subdirectory( dependencies/MyGui/Common/MessageBox )
add_subdirectory( dependencies/MyGui/Common/Ogre )
add_subdirectory( dependencies/MyGui/Common/PanelView )
add_subdirectory( dependencies/MyGui/Common/Tools )
add_subdirectory( dependencies/MyGui/MyGUIEngine )
add_subdirectory( dependencies/MyGui/Platforms/Ogre/OgrePlatform )
add_subdirectory( dependencies/MyGui/Platforms/OpenGL/OpenGLPlatform )
add_subdirectory( dependencies/MyGui/Tools/FontViewer )
add_subdirectory( dependencies/MyGui/Tools/ImageSetViewer )
add_subdirectory( dependencies/MyGui/Tools/LayoutEditor )
add_subdirectory( dependencies/MyGui/Tools/SkinEditor )
add_subdirectory( dependencies/OIS )
add_subdirectory( dependencies/pcre )
add_subdirectory( dependencies/uuid )
add_subdirectory( dependencies/zlib )
add_subdirectory( dependencies/zziplib )
add_subdirectory( gucefANDROIDGLUE/Gingerbread/jni )
add_subdirectory( gucefCOM )
add_subdirectory( gucefCOMCORE )
add_subdirectory( gucefCORE )
add_subdirectory( gucefDRN )
add_subdirectory( gucefGUI )
add_subdirectory( gucefIMAGE )
add_subdirectory( gucefINPUT )
add_subdirectory( gucefLOADER )
add_subdirectory( gucefMATH )
add_subdirectory( gucefMT )
add_subdirectory( gucefMULTIPLAY )
add_subdirectory( gucefPATCHER )
add_subdirectory( gucefPRODMAN )
add_subdirectory( gucefSMDRN )
add_subdirectory( gucefVFS )
add_subdirectory( plugins/CORE/dstorepluginPARSIFALXML )
add_subdirectory( plugins/GUI/guidriverAndroidGLES )
add_subdirectory( plugins/GUI/guidriverCEGUI )
add_subdirectory( plugins/GUI/guidriverCEGUIOpenGL )
add_subdirectory( plugins/GUI/guidriverMyGUI )
add_subdirectory( plugins/GUI/guidriverMyGUIOpenGL )
add_subdirectory( plugins/GUI/guidriverMyGUIOpenGL/OpenGLESPlatform )
add_subdirectory( plugins/GUI/guidriverRocket )
add_subdirectory( plugins/GUI/guidriverRocketOpenGL )
add_subdirectory( plugins/GUI/guidriverWin32GL )
add_subdirectory( plugins/GUI/guidriverXWinGL )
add_subdirectory( plugins/IMAGE/imgpluginDEVIL )
add_subdirectory( plugins/IMAGE/imgpluginFreeImage )
add_subdirectory( plugins/IMAGE/imgpluginITV )
add_subdirectory( plugins/INPUT/inputdriverDIRECTINPUT8 )
add_subdirectory( plugins/INPUT/inputdriverMSWINMSG )
add_subdirectory( plugins/INPUT/inputdriverNANDROID )
add_subdirectory( plugins/INPUT/inputdriverOIS )
add_subdirectory( plugins/INPUT/inputdriverXWINMSG )
add_subdirectory( plugins/VFS/vfspluginDVP )
add_subdirectory( plugins/VFS/vfspluginITV )
add_subdirectory( plugins/VFS/vfspluginVP )
add_subdirectory( plugins/VFS/vfspluginZIP )
add_subdirectory( tests/gucefCOMCORE_TestApp )
add_subdirectory( tests/gucefCOM_TestApp )
add_subdirectory( tests/gucefCORE_TestApp )
add_subdirectory( tests/gucefDRN_TestApp )
add_subdirectory( tests/gucefGUI_TestApp )
add_subdirectory( tests/gucefIMAGE_TestApp )
add_subdirectory( tests/gucefINPUT_TestApp )
add_subdirectory( tests/gucefLOADER_TestApp )
add_subdirectory( tests/gucefMT_TestApp )
add_subdirectory( tests/gucefPATCHERAPP_TestApp )
add_subdirectory( tests/gucefPRODMAN_TestApp )
add_subdirectory( tests/MemoryLeakFinder_TestApp )
add_subdirectory( tools/ArchiveDiff )
add_subdirectory( tools/ArchiveDiffLib )
add_subdirectory( tools/CMakeListGenerator )
add_subdirectory( tools/DCSBruteInstaller )
add_subdirectory( tools/DuplicateFileFinder )
add_subdirectory( tools/DVPPackTool )
add_subdirectory( tools/FileDiff )
add_subdirectory( tools/FileReplacer )
add_subdirectory( tools/GucefArchiver )
add_subdirectory( tools/GucefLogServiceApp )
add_subdirectory( tools/GucefLogServiceClientPlugin )
add_subdirectory( tools/GucefLogServiceLib )
add_subdirectory( tools/GucefLogService_TestApp )
add_subdirectory( tools/HDFiller )
add_subdirectory( tools/MemoryLeakFinder )
add_subdirectory( tools/PatcherGUI/MFCPatcherGUI )
add_subdirectory( tools/PatchSetGenerator )
add_subdirectory( tools/ProjectGen )
add_subdirectory( tools/ProjectGen/plugins/ProjectGenDependsFilter )
add_subdirectory( tools/ProjectGen/plugins/ProjectGenVSImporter )
add_subdirectory( tools/ProjectGenerator )
add_subdirectory( tools/ReferenceUpdater )
add_subdirectory( tools/ServerPortExtender )
add_subdirectory( tools/SocketSink )
add_subdirectory( tools/SVNMagicMerge )
