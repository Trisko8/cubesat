cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Cubesat)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(cubesat cubesat.cc ${sources} ${headers})
target_link_libraries(cubesat ${Geant4_LIBRARIES})

set(CUBESAT_SCRIPTS
  run.mac
  vis.mac
  )

foreach(_script ${CUBESAT_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

add_custom_target(Cubesat DEPENDS cubesat)
