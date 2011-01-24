# this file create binary of CEG in including all sources files

SET(SAMPLE_SRCS
  main.cpp
  About.cpp
  Accounts.cpp
  AccountsAdmin.cpp
  Action.cpp
  Client.cpp
  Connect.cpp
  Contact.cpp
  Create.cpp
  Credit.cpp
  Database.cpp
  Lang.cpp
  Message.cpp
  News.cpp
  Options.cpp
  Service.cpp
  Socket.cpp
  State.cpp
  Stream.cpp
  Web.cpp
)

#QT4_AUTOMOC(${SOURCES})

# Use of qt4_wrap_cpp and qt4_automoc:
# http://qtnode.net/wiki/Qt4_with_cmake

# Here is an explaination to how to use qt4_wrap_cpp:
# http://www.mail-archive.com/cmake@cmake.org/msg18900.html

SET(SAMPLE_UIS
  ${QLIK_CLIENT_SRC_DIR}/forms/settings.ui
)

SET(SAMPLE_MOC_HDRS
  ${QLIK_CLIENT_SRC_DIR}/includes/Systray.h
  ${QLIK_CLIENT_SRC_DIR}/includes/Settings.h
  ${QLIK_CLIENT_SRC_DIR}/includes/CegTcpServer.h
  )

SET(SAMPLE_RCS
  ${QLIK_CLIENT_SRC_DIR}/resources/resources.qrc
  )

SET(EXECUTABLE_OUTPUT_PATH ${QLIK_CLIENT_BIN_DIR})

QT4_WRAP_UI(SAMPLE_UIS_SRCS ${SAMPLE_UIS})
QT4_WRAP_CPP(SAMPLE_MOC_SRCS ${SAMPLE_MOC_HDRS})
QT4_ADD_RESOURCES(SAMPLE_RC_SRCS ${SAMPLE_RCS})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(${PROJECT_NAME} ${SAMPLE_SRCS} ${SAMPLE_UIS_SRCS} ${SAMPLE_MOC_SRCS} ${SAMPLE_RC_SRCS} )

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES})

INSTALL(
  TARGETS ${PROJECT_NAME}
  RUNTIME
  DESTINATION bin
  COMPONENT applications
  )
