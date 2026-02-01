# Custom configuration for benchmarks
add_library(BenchConfiguration INTERFACE)
target_link_libraries(BenchConfiguration INTERFACE BaseConfiguration)
if(BUILD_TYPE STREQUAL "Release")
    # Add custom optimization flags here:
    target_compile_options(BenchConfiguration INTERFACE -O0)
else()
    target_link_libraries(BenchConfiguration INTERFACE BaseOptConfiguration)
endif()

function(add_perf_test ALORITHM_NAME MOD)
    set(BENCH_NAME ${ALORITHM_NAME}_${MOD}_perf)
    add_executable(${BENCH_NAME}
                   "${CMAKE_CURRENT_SOURCE_DIR}/src/${ALORITHM_NAME}.cpp")

    target_include_directories(${BENCH_NAME}
                               PUBLIC
                                 ${PROJECT_SOURCE_DIR}/perf/include
                                 ${PROJECT_SOURCE_DIR}/lib/include)


    target_link_libraries(${BENCH_NAME}
                          PUBLIC
                            algorithms
                          PRIVATE
                            BenchConfiguration)

    target_compile_definitions(${BENCH_NAME} PRIVATE -D${MOD})
endfunction()

add_perf_test(abs scalar)
add_perf_test(abs rvv)

add_perf_test(axpby scalar)
add_perf_test(axpby rvv)

add_perf_test(dot scalar)
add_perf_test(dot rvv)

add_perf_test(strlen scalar)
add_perf_test(strlen rvv)

add_perf_test(iamin scalar)
add_perf_test(iamin rvv)

add_perf_test(nrm2 scalar)
add_perf_test(nrm2 rvv)

add_perf_test(gemv scalar)
add_perf_test(gemv rvv)

add_perf_test(symv scalar)
add_perf_test(symv rvv)

add_perf_test(gemm scalar)
add_perf_test(gemm rvv)

add_perf_test(alpha_compositing scalar)
add_perf_test(alpha_compositing rvv)

add_perf_test(blur_filter scalar)
add_perf_test(blur_filter rvv)
