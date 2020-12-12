cmake_minimum_required(VERSION 3.10)
project(cleancode2020)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}
set(CMAKE_BUILD_TYPE DEBUG
    CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel Sanitizer"
FORCE)

##################################################################################################
## Quality check settings
set(sanitizerflags "-fsanitize=address -fno-optimize-sibling-calls -fsanitize-address-use-after-scope")
#set(sanitizerflags "${sanitizerflags} -fsanitize=thread -g -O1")
set(sanitizerflags "${sanitizerflags} -fsanitize=leak")
# set(sanitizerflags "${sanitizerflags} -fsanitize=memory -fsanitize-memory-track-origins=2")
set(sanitizerflags "${sanitizerflags} -fsanitize=undefined")

set(CMAKE_CXX_FLAGS_SANITIZER
    ${sanitizerflags}
    CACHE STRING "Flags used by the C++ compiler during Sanitizer builds."
    FORCE)

if (ENABLE_CPPCHECK)
    set(CMAKE_CXX_CPPCHECK "cppcheck")
    list(APPEND CMAKE_CXX_CPPCHECK "--error-exitcode=1")
endif()

enable_testing()
if (ENABLE_VALGRIND)
    find_program(MEMORYCHECK_COMMAND valgrind)
    set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full" "--suppressions=${PROJECT_SOURCE_DIR}/valgrind.supp")
endif()

# Common libraries
find_package(GTest REQUIRED)
find_package(Boost REQUIRED COMPONENTS regex date_time)
include_directories(${GTEST_INCLUD_DIRS})
include_directories(${Boost_INCLUD_DIRS})

# Hints: Add additional include directories by 
#  include_directories(/path/to/your/include/folder [folder1] ...)

###################################################################################################
# Source file lists
set(srcs 
    # Hints: Add additional source files to this list, one file per line
    src/main.cpp
    src/Distribution_App.cpp
    src/Distribution_App.hpp
    src/Manifest.cpp
    src/Manifest.hpp
    src/Pool.cpp
    src/Pool.hpp
    src/Algorithm.cpp
    src/Algorithm.hpp
    src/IO.cpp
    src/IO.hpp
)

###################################################################################################
# Test source file list
set(test-srcs
    # Hints: Add additional test files to this list, one file per line
    test/test1.cpp
    src/Distribution_App.cpp
    src/Distribution_App.hpp
    src/Manifest.cpp
    src/Manifest.hpp
    src/Pool.cpp
    src/Pool.hpp
    src/Algorithm.cpp
    src/Algorithm.hpp
    src/IO.cpp
    src/IO.hpp
)

###################################################################################################
# Executables, tests
add_executable(main ${srcs})
add_executable(unit-test ${test-srcs})
target_link_libraries(unit-test GTest::GTest GTest::Main)

foreach(exename main unit-test)
    target_link_libraries(${exename}
        ${Boost_LIBRARIES}
    )
endforeach()

add_test(NAME unittest COMMAND unit-test)
add_test(NAME integration 
    COMMAND bash "${CMAKE_CURRENT_SOURCE_DIR}/integration_test.sh" "$<TARGET_FILE:main>" ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(ut COMMAND ${CMAKE_CTEST_COMMAND} -R unit -V
    DEPENDS unit-test
    COMMENT "Running unit tests...")

add_custom_target(it COMMAND ${CMAKE_CTEST_COMMAND} -R integration -V
    DEPENDS main
    COMMENT "Running integration tests..."
)

if (ENABLE_VALGRIND)
    set(VALGRIND_OPTIONS "${MEMORYCHECK_COMMAND}" "${MEMORYCHECK_COMMAND_OPTIONS}")
    add_custom_target(memcheck
        COMMAND mkdir -p "${CMAKE_BINARY_DIR}/Testing/Temporary/"
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/check_valgrind.sh ${CMAKE_CURRENT_BINARY_DIR}/check_valgrind.sh
        COMMAND bash "${MEMORYCHECK_COMMAND}" ${MEMORYCHECK_COMMAND_OPTIONS} --log-file=${CMAKE_CURRENT_BINARY_DIR}/Testing/Temporary/MemoryChecker-ut.log "$<TARGET_FILE:unit-test>" 
        COMMAND bash check_valgrind.sh ${CMAKE_CURRENT_BINARY_DIR}/Testing/Temporary/MemoryChecker-ut.log
        COMMAND bash "${CMAKE_CURRENT_SOURCE_DIR}/integration_test.sh" "$<TARGET_FILE:main>" ${CMAKE_CURRENT_SOURCE_DIR} ${VALGRIND_OPTIONS}
        DEPENDS main unit-test
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running memeory checks"
        )
endif()
