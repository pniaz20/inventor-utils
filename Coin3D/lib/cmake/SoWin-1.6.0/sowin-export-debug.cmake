#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SoWin::SoWin" for configuration "Debug"
set_property(TARGET SoWin::SoWin APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SoWin::SoWin PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/SoWin1d.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/SoWin1d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS SoWin::SoWin )
list(APPEND _IMPORT_CHECK_FILES_FOR_SoWin::SoWin "${_IMPORT_PREFIX}/lib/SoWin1d.lib" "${_IMPORT_PREFIX}/bin/SoWin1d.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
