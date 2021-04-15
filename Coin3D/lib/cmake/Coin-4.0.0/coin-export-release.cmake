#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Coin::Coin" for configuration "Release"
set_property(TARGET Coin::Coin APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Coin::Coin PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Coin4.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Coin4.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Coin::Coin )
list(APPEND _IMPORT_CHECK_FILES_FOR_Coin::Coin "${_IMPORT_PREFIX}/lib/Coin4.lib" "${_IMPORT_PREFIX}/bin/Coin4.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
