cmake_minimum_required(VERSION 3.16)
project(behavioral_evoltion VERSION 0.1.0)

include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -fsanitize=address")

string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

add_executable(main main.cpp population.cpp individual.cpp rnghelper.cpp graphic.cpp logical.cpp simulation.cpp)

#-DBUILD_TESTING=OFF per disabilitare i test
if (BUILD_TESTING)

  add_executable(test main.test.cpp population.cpp individual.cpp rnghelper.cpp graphic.cpp logical.cpp simulation.cpp)

  add_test(NAME test COMMAND test)

endif()