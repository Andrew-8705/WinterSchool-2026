function(add_test ALORITHM_NAME MOD)
    add_executable(${ALORITHM_NAME}_${MOD}_test
                  "${CMAKE_CURRENT_SOURCE_DIR}/src/${ALORITHM_NAME}/${ALORITHM_NAME}_test.cpp"
                  "${CMAKE_CURRENT_SOURCE_DIR}/src/${ALORITHM_NAME}/${ALORITHM_NAME}_ref.cpp")

    target_include_directories(${ALORITHM_NAME}_${MOD}_test
                               PUBLIC
                               ${PROJECT_SOURCE_DIR}/test/include
                               ${PROJECT_SOURCE_DIR}/3rd-party/gtest/googletest/include
                               ${PROJECT_SOURCE_DIR}/lib/include)

    target_link_libraries(${ALORITHM_NAME}_${MOD}_test
    PUBLIC
        GTest::gtest
        GTest::gtest_main
        algorithms
    PRIVATE
        CommonConfiguration
    )

    target_compile_definitions(${ALORITHM_NAME}_${MOD}_test PRIVATE -D${MOD})
endfunction()

add_test(abs scalar)
add_test(abs rvv)

add_test(dot scalar)
add_test(dot rvv)

add_test(axpby scalar)
add_test(axpby rvv)

add_test(strlen scalar)
add_test(strlen rvv)

add_test(iamin scalar)
add_test(iamin rvv)

add_test(nrm2 scalar)
add_test(nrm2 rvv)

add_test(gemv scalar)
add_test(gemv rvv)

add_test(symv scalar)
add_test(symv rvv)

add_test(gemm scalar)
add_test(gemm rvv)

add_test(alpha_compositing scalar)
add_test(alpha_compositing rvv)

add_test(blur_filter scalar)
add_test(blur_filter rvv)