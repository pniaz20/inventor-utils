#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Coin::Coin" for configuration "Debug"
set_property(TARGET Coin::Coin APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Coin::Coin PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/Coin4d.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/Coin4d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Coin::Coin )
list(APPEND _IMPORT_CHECK_FILES_FOR_Coin::Coin "${_IMPORT_PREFIX}/lib/Coin4d.lib" "${_IMPORT_PREFIX}/bin/Coin4d.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
