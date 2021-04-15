# CMake package configuration file for SoWin
#
# Defines the target "SoWin::SoWin"
#
# Add the following lines to your CMakeLists.txt to depend on SoWin
#
#    find_package(SoWin REQUIRED)
#    target_link_libraries(my_target_name SoWin::SoWin)
#
# Additionally you may one of the following variables (or their corresponding
# upper case version) that are also defined.
#
# SoWin_COMPILE_DEFINITIONS
# SoWin_DEFINITIONS
# SoWin_INCLUDE_DIRS
# SoWin_INCLUDE_DIR
# SoWin_LIBRARY
# SoWin_LIBRARIES
# SoWin_LIBRARY_DIRS
# SoWin_LIBRARY_DIR
#
# However, in most cases using the SoWin::SoWin target is sufficient,
# and you won't need these variables.


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was sowin-config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

include(CMakeFindDependencyMacro)

find_dependency(Coin REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/sowin-export.cmake")

get_property(SoWin_COMPILE_DEFINITIONS TARGET SoWin::SoWin PROPERTY INTERFACE_COMPILE_DEFINITIONS)
foreach(_def ${SoWin_COMPILE_DEFINITIONS})
  list(APPEND SoWin_DEFINITIONS -D${_def})
endforeach()

set(SoWin_VERSION 1.6.0)

get_property(SoWin_INCLUDE_DIRS TARGET SoWin::SoWin PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
set(SoWin_INCLUDE_DIR ${SoWin_INCLUDE_DIRS})
set(SoWin_LIBRARY SoWin::SoWin)
get_property(SoWin_LIBRARIES TARGET SoWin::SoWin PROPERTY INTERFACE_LINK_LIBRARIES)
set(SoWin_LIBRARIES SoWin::SoWin ${SoWin_LIBRARIES})

set_and_check(SoWin_LIBRARY_DIRS "${PACKAGE_PREFIX_DIR}/lib")
set(SoWin_LIBRARY_DIR ${SoWin_LIBRARY_DIRS})

# For backwards compatibility define upper case versions of output variables
foreach(_var
  SoWin_COMPILE_DEFINITIONS
  SoWin_DEFINITIONS
  SoWin_INCLUDE_DIRS
  SoWin_INCLUDE_DIR
  SoWin_LIBRARY
  SoWin_LIBRARIES
  SoWin_LIBRARY_DIRS
  SoWin_LIBRARY_DIR
  SoWin_VERSION
  )
  string(TOUPPER ${_var} _uppercase_var)
  set(${_uppercase_var} ${${_var}})
endforeach()
