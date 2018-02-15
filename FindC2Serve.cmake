#
#  Script to find necessary C2Serve includes and libraries
#  This script sets the following variables:
#    C2Serve_INCLUDE_DIRS - List of include directories
#    C2Serve_LINK_LIB_DIR - Directory containing C2Serve libraries
#    C2Serve_LIBRARIES    - List of libraries
#    C2Serve_FOUND        - True if all necessary C2Serve components have been found
#

if ( NOT DEFINED C2Serve_ROOT_DIR )
  #TODO: Search all possible install paths
  set( C2Serve_ROOT_DIR /usr/local )
endif( NOT DEFINED C2Serve_ROOT_DIR )

message( STATUS "C2Serve root directory: " ${C2Serve_ROOT_DIR} )

set( C2Serve_FOUND TRUE )

#########################################################################
#################### COMPONENTS #########################################

set( C2Serve_COMPONENT_SERVER FALSE )
set( C2Serve_COMPONENT_CLIENT FALSE )

foreach( COMPONENT ${C2Serve_FIND_COMPONENTS} )
  if( ${COMPONENT} MATCHES server )
    set( C2Serve_COMPONENT_SERVER TRUE )
  elseif( ${COMPONENT} MATCHES client )
    set( C2Serve_COMPONENT_CLIENT TRUE )
  else( ${COMPONENT} MATCHES server )
    message( FATAL_ERROR "Unknown C2Serve component: " ${COMPONENT} )
  endif( ${COMPONENT} MATCHES server )
endforeach( COMPONENT ${C2Serve_FIND_COMPONENTS} )

if ( NOT C2Serve_COMPONENT_SERVER AND NOT C2Serve_COMPONENT_CLIENT )
  set( C2Serve_COMPONENT_SERVER TRUE )
  set( C2Serve_COMPONENT_CLIENT TRUE )
endif ( NOT C2Serve_COMPONENT_SERVER AND NOT C2Serve_COMPONENT_CLIENT )

#########################################################################
#################### INCLUDES ###########################################

if ( NOT DEFINED C2Serve_INCLUDE_ROOT_DIR )
  set( C2Serve_INCLUDE_ROOT_DIR ${C2Serve_ROOT_DIR}/include/c2s )
endif ( NOT DEFINED C2Serve_INCLUDE_ROOT_DIR )

set( C2S_INCLUDE_DIRS_RELATIVE
  c2s-log
  c2s-util
  c2s-util/io
  c2s-core
  c2s-http
  c2s-rest
)

foreach( C2S_CURRENT_INCLUDE_DIR_RELATIVE ${C2S_INCLUDE_DIRS_RELATIVE} )
  set( C2S_CURRENT_INCLUDE_DIR_ABSOLUTE ${C2Serve_INCLUDE_ROOT_DIR}/${C2S_CURRENT_INCLUDE_DIR_RELATIVE} )
  if ( NOT EXISTS ${C2S_CURRENT_INCLUDE_DIR_ABSOLUTE} )
    set( C2Serve_FOUND FALSE )
    set( C2S_MISSING_INCLUDES ${C2S_MISSING_INCLUDES} ${C2S_CURRENT_INCLUDE_DIR_ABSOLUTE} )
  else ( NOT EXISTS ${C2S_CURRENT_INCLUDE_DIR_ABSOLUTE} )
    set( C2Serve_INCLUDE_DIRS ${C2Serve_INCLUDE_DIRS} ${C2S_CURRENT_INCLUDE_DIR_ABSOLUTE} )
  endif ( NOT EXISTS ${C2S_CURRENT_INCLUDE_DIR_ABSOLUTE} )
endforeach( C2S_CURRENT_INCLUDE_DIR_RELATIVE ${C2S_INCLUDE_DIRS_RELATIVE} )

#########################################################################

#########################################################################
#################### LIBRARIES ##########################################

if ( NOT DEFINED C2Serve_LINK_LIB_DIR )
  set( C2Serve_LINK_LIB_DIR ${C2Serve_ROOT_DIR}/lib )
endif ( NOT DEFINED C2Serve_LINK_LIB_DIR )

set( C2Serve_LIBRARIES
  c2s_http
  c2s_util
)

if ( C2Serve_COMPONENT_SERVER )
  set( C2Serve_LIBRARIES
    c2s_rest
    ${C2Serve_LIBRARIES}
    c2s_core
    c2s_socket
    c2s_log
  )
endif ( C2Serve_COMPONENT_SERVER )

if ( C2Serve_COMPONENT_CLIENT )
  set( C2Serve_LIBRARIES
    c2s_httpclient
    ${C2Serve_LIBRARIES}
  )
endif ( C2Serve_COMPONENT_CLIENT )

foreach( C2S_CURRENT_LIBRARY ${C2Serve_LIBRARIES} )
  set( C2S_CURRENT_LIBRARY_ABSOLUTE_FILENAME ${C2Serve_LINK_LIB_DIR}/lib${C2S_CURRENT_LIBRARY}.a )
  if ( NOT EXISTS ${C2S_CURRENT_LIBRARY_ABSOLUTE_FILENAME} AND NOT DEFINED C2Serve_SKIP_CHECK_IF_LIBS_EXIST )
    set( C2Serve_FOUND FALSE )
    set( C2S_MISSING_LIBRARIES ${C2S_MISSING_LIBRARIES} ${C2S_CURRENT_LIBRARY} )
  endif ( NOT EXISTS ${C2S_CURRENT_LIBRARY_ABSOLUTE_FILENAME} AND NOT DEFINED C2Serve_SKIP_CHECK_IF_LIBS_EXIST )
endforeach( C2S_CURRENT_LIBRARY ${C2Serve_LIBRARIES} )

if ( C2Serve_FOUND )
  link_directories( ${C2Serve_LINK_LIB_DIR} )
endif( C2Serve_FOUND )

#########################################################################

#########################################################################
#################### PRINT INFOS ########################################

if ( NOT C2Serve_FOUND )

  message( STATUS "Could NOT find C2Serve" )
  
  if ( C2S_MISSING_INCLUDES )
    message( STATUS " Missing include paths:" )
    foreach( C2S_MISSING_INCLUDE ${C2S_MISSING_INCLUDES} )
      message( STATUS "  " ${C2S_MISSING_INCLUDE} )  
    endforeach( C2S_MISSING_INCLUDE ${C2S_MISSING_INCLUDES} )
  endif( C2S_MISSING_INCLUDES )
  
  if ( C2S_MISSING_LIBRARIES )
    message( STATUS " Missing libraries:" )
    foreach( C2S_MISSING_LIBRARY ${C2S_MISSING_LIBRARIES} )
      message( STATUS "  " ${C2S_MISSING_LIBRARY} )  
    endforeach( C2S_MISSING_LIBRARY ${C2S_MISSING_LIBRARIES} )
    message( STATUS " Path searched for libraries: " ${C2Serve_LINK_LIB_DIR} )
  endif( C2S_MISSING_LIBRARIES )
  
endif ( NOT C2Serve_FOUND )

#########################################################################
