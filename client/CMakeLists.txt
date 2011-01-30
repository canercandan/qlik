######################################################################################
### 1) Set the application properties
######################################################################################

# Checks cmake version compatibility
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(client)

SET(PROJECT_VERSION_MAJOR 1)
SET(PROJECT_VERSION_MINOR 0)
SET(PROJECT_VERSION_PATCH 0)
SET(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

######################################################################################


######################################################################################
### 2) Prepare some useful variables
######################################################################################

SET(QLIK_CLIENT_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
SET(QLIK_CLIENT_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}")

######################################################################################


######################################################################################
### 3) Include useful features
######################################################################################

INCLUDE(FindDoxygen)

# see http://cmake.org/cmake/help/cmake2.6docs.html#module:FindQt4 for a complete list
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtNetwork QtXml QtSql REQUIRED)
INCLUDE(${QT_USE_FILE})

######################################################################################


######################################################################################
### 4) Include header files path
######################################################################################

INCLUDE_DIRECTORIES(
#  ${CMAKE_CURRENT_SOURCE_DIR}/includes
#  ${CMAKE_CURRENT_SOURCE_DIR}/includes/Action
  )

######################################################################################


######################################################################################
### 5) Set compiler definitions
######################################################################################

IF(UNIX)
  # enable warnings
  ADD_DEFINITIONS( -Wall -W -Wextra )
  # ADD_DEFINITIONS( -Weffc++)
#   ADD_DEFINITIONS( -g3 )
ENDIF()

######################################################################################


######################################################################################
### 6) Now where we go ?
######################################################################################

ADD_SUBDIRECTORY(src)
#ADD_SUBDIRECTORY(config)
#ADD_SUBDIRECTORY(resources)
#ADD_SUBDIRECTORY(test)
#ADD_SUBDIRECTORY(doc)

######################################################################################


######################################################################################
### 7) Include packaging
######################################################################################

INCLUDE(Packaging.cmake)

######################################################################################
