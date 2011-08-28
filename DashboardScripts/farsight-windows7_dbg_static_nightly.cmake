SET(CTEST_SOURCE_NAME "src/farsight")
SET(CTEST_BINARY_NAME "bin/farsight-static")
SET(CTEST_DASHBOARD_ROOT "C:/dashboard")
SET(CTEST_SOURCE_DIRECTORY "${CTEST_DASHBOARD_ROOT}/${CTEST_SOURCE_NAME}")
SET(CTEST_BINARY_DIRECTORY "${CTEST_DASHBOARD_ROOT}/${CTEST_BINARY_NAME}")

SET (CTEST_START_WITH_EMPTY_BINARY_DIRECTORY TRUE)

SET(CTEST_COMMAND
  "\"c:/Program Files (x86)/CMake 2.8/bin/ctest.exe\" -V -VV -D Nightly -A \"${CTEST_SCRIPT_DIRECTORY}/${CTEST_SCRIPT_NAME}\""
  )

SET(CTEST_CMAKE_COMMAND
  "\"c:/Program Files (x86)/CMake 2.8/bin/cmake.exe\""
  )

SET(CTEST_INITIAL_CACHE "
SITE:STRING=farsight-win_7_64
BUILDNAME:STRING=vs9-64-dbg-static
CMAKE_GENERATOR:INTERNAL=Visual Studio 9 2008 Win64
MAKECOMMAND:STRING=C:/PROGRA~2/MICROS~10/Common7/IDE/devenv.com Farsight.sln /build Debug /project ALL_BUILD
BUILD_SHARED_LIBS:BOOL=OFF
ITK_DIR:PATH=C:/dashboard/bin/itkv4.0a09
VTK_DIR:PATH=C:/dashboard/bin/vtk-5.6.1
VXL_DIR:PATH=C:/dashboard/bin/vxl-1.14.0
Boost_INCLUDE_DIR:PATH=C:/dashboard/src/boost_1_47_0
QT_QMAKE_EXECUTABLE:FILEPATH=C:/Qt/4.7.2/bin/qmake.exe
")

SET(CTEST_CVS_COMMAND "C:/Program Files/TortoiseSVN/bin/TortoiseProc.exe")

