cmake_minimum_required(VERSION 3.16)
project(behavioral_evoltion VERSION 0.1.0)

include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# -DUSE_ROOT=OFF per disabilitare
option(USE_ROOT "Use root to add the possibility of printing graphs" ON)

if(USE_ROOT)

find_package(ROOT)

if(ROOT_FOUND)

add_compile_definitions(MY_ROOT)

message(ROOT=${ROOT_INCLUDE_DIRS})

add_executable(main main.cpp population.cpp individual.cpp rnghelper.cpp graphic.cpp simulation.cpp roothelper.cpp)

target_link_libraries(main ${ROOT_LIBRARIES})
target_include_directories(main PUBLIC ${ROOT_INCLUDE_DIRS})

else() 

add_executable(main main.cpp population.cpp individual.cpp rnghelper.cpp graphic.cpp simulation.cpp)

endif(ROOT_FOUND)

else()

  add_compile_definitions(DISABLED_ROOT)

  add_executable(main main.cpp population.cpp individual.cpp rnghelper.cpp graphic.cpp simulation.cpp)

endif(USE_ROOT)

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -fsanitize=address")

string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

#-DBUILD_TESTING=OFF per disabilitare i test
if (BUILD_TESTING)

if(USE_ROOT)

if(ROOT_FOUND)

add_executable(main.test main.test.cpp population.cpp individual.cpp rnghelper.cpp graphic.cpp simulation.cpp roothelper.cpp)

target_link_libraries(main.test ${ROOT_LIBRARIES})
target_include_directories(main.test PUBLIC ${ROOT_INCLUDE_DIRS})

else()

add_executable(main.test main.test.cpp population.cpp individual.cpp rnghelper.cpp graphic.cpp simulation.cpp)

endif(ROOT_FOUND)

else()

add_executable(main.test main.test.cpp population.cpp individual.cpp rnghelper.cpp graphic.cpp simulation.cpp)

endif(USE_ROOT)


  add_test(NAME main.test COMMAND main.test)

endif()