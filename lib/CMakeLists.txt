set(LIBRARY_NAME "algorithms")

# Create main library
add_library(${LIBRARY_NAME} STATIC)

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${LIBRARY_NAME} PRIVATE CommonScalarConfiguration)

function(add_obj_lib_scalar OBJ_NAME CONFIGURATION)
    add_library(${OBJ_NAME}_scalar OBJECT "${CMAKE_CURRENT_SOURCE_DIR}/src/scalar/${OBJ_NAME}.c")
    target_include_directories(${OBJ_NAME}_scalar PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${OBJ_NAME}_scalar PRIVATE ${CONFIGURATION})
    target_link_libraries(${LIBRARY_NAME} PRIVATE ${OBJ_NAME}_scalar)
endfunction()

function(add_obj_lib_rvv OBJ_NAME CONFIGURATION)
    add_library(${OBJ_NAME}_rvv OBJECT "${CMAKE_CURRENT_SOURCE_DIR}/src/rvv/${OBJ_NAME}.c")
    target_include_directories(${OBJ_NAME}_rvv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${OBJ_NAME}_rvv PRIVATE ${CONFIGURATION})
    target_link_libraries(${LIBRARY_NAME} PRIVATE ${OBJ_NAME}_rvv)
endfunction()

# Custom configuration for separate files with scalar impl
add_library(CustomScalarConfiguration INTERFACE)
target_link_libraries(CustomScalarConfiguration INTERFACE BaseScalarConfiguration)
if(BUILD_TYPE STREQUAL "Release")
    # Add custom optimization flags here:
    target_compile_options(CustomScalarConfiguration INTERFACE -O3)
else()
    target_link_libraries(CustomScalarConfiguration INTERFACE BaseOptConfiguration)
endif()

# Custom configuration for separate files with RVV optimization
add_library(CustomVectorConfiguration INTERFACE)
target_link_libraries(CustomVectorConfiguration INTERFACE BaseConfiguration)
if(BUILD_TYPE STREQUAL "Release")
    # Add custom optimization flags here:
    target_compile_options(CustomVectorConfiguration INTERFACE -O3)
else()
    target_link_libraries(CustomVectorConfiguration INTERFACE BaseOptConfiguration)
endif()

#
# Object libraries with separate compiler keys
#
add_obj_lib_scalar("abs" CommonScalarConfiguration)
add_obj_lib_scalar("axbpy" CommonScalarConfiguration)
add_obj_lib_scalar("dot" CommonScalarConfiguration)
add_obj_lib_scalar("nrm2" CommonScalarConfiguration)
add_obj_lib_scalar("iamin" CommonScalarConfiguration)
add_obj_lib_scalar("alpha_compositing" CommonScalarConfiguration)
add_obj_lib_scalar("blur_filter" CommonScalarConfiguration)
add_obj_lib_scalar("gemm" CommonScalarConfiguration)
add_obj_lib_scalar("strlen" CommonScalarConfiguration)
add_obj_lib_scalar("gemv" CommonScalarConfiguration)
add_obj_lib_scalar("symv" CommonScalarConfiguration)

add_obj_lib_rvv("abs" CommonConfiguration)
add_obj_lib_rvv("axbpy" CommonConfiguration)
add_obj_lib_rvv("dot" CommonConfiguration)
add_obj_lib_rvv("nrm2" CommonConfiguration)
add_obj_lib_rvv("iamin" CommonConfiguration)
add_obj_lib_rvv("alpha_compositing" CommonConfiguration)
add_obj_lib_rvv("blur_filter" CommonConfiguration)
add_obj_lib_rvv("gemm" CommonConfiguration)
add_obj_lib_rvv("strlen" CommonConfiguration)
add_obj_lib_rvv("gemv" CommonConfiguration)
add_obj_lib_rvv("symv" CommonConfiguration)
