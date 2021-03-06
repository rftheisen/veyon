include(BuildVeyonApplication)
include(WindowsBuildHelpers)

set(kitemmodels_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/kitemmodels/src/core)
set(kitemmodels_SOURCES
	${kitemmodels_SOURCE_DIR}/kextracolumnsproxymodel.cpp
	${kitemmodels_SOURCE_DIR}/krecursivefilterproxymodel.cpp
	${kitemmodels_SOURCE_DIR}/kextracolumnsproxymodel.h
	${kitemmodels_SOURCE_DIR}/krecursivefilterproxymodel.h
)

file(GLOB master_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB master_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui)

set(master_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources/master.qrc)
if(VEYON_DEBUG)
set(master_RESOURCES ${master_RESOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/resources/examples.qrc)
endif()
set(master_RESOURCES ${master_RESOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/qml/qml.qrc)

build_veyon_application(veyon-master ${master_SOURCES} ${master_INCLUDES} ${master_RESOURCES} ${kitemmodels_SOURCES})
target_include_directories(veyon-master PRIVATE ${kitemmodels_SOURCE_DIR})

add_windows_resource(veyon-master)
make_graphical_app(veyon-master)

if(VEYON_BUILD_LINUX)
	xdg_install(${CMAKE_CURRENT_BINARY_DIR}/data/veyon-master.desktop ${CMAKE_CURRENT_SOURCE_DIR}/data/veyon-master.xpm ${CMAKE_CURRENT_SOURCE_DIR}/data/veyon-master.png ${CMAKE_CURRENT_SOURCE_DIR}/data/veyon-master.svg)
endif()

cotire_veyon(veyon-master)
