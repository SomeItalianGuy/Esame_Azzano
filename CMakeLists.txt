cmake_minimum_required(VERSION 3.16)
project(behavioral_evoltion VERSION 0.1.0)

include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

find_package(ROOT)

if(ROOT_FOUND)

add_compile_definitions(MY_ROOT)

message(ROOT=${ROOT_INCLUDE_DIRS})
  
add_executable(main main.cpp population.cpp individual.cpp rnghelper.cpp graphic.cpp simulation.cpp roothelper.cpp)

target_link_libraries(main ${ROOT_LIBRARIES})
target_include_directories(main PUBLIC ${ROOT_INCLUDE_DIRS})

else() # TODO add the option to disable root

add_executable(main main.cpp population.cpp individual.cpp rnghelper.cpp graphic.cpp simulation.cpp)

endif()

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -fsanitize=address")

string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

#-DBUILD_TESTING=OFF per disabilitare i test
if (BUILD_TESTING)

if(ROOT_FOUND)

add_executable(main.test main.test.cpp population.cpp individual.cpp rnghelper.cpp graphic.cpp simulation.cpp roothelper.cpp)

target_link_libraries(main.test ${ROOT_LIBRARIES})
target_include_directories(main.test PUBLIC ${ROOT_INCLUDE_DIRS})

else()

add_executable(main.test main.test.cpp population.cpp individual.cpp rnghelper.cpp graphic.cpp simulation.cpp)

endif()


  add_test(NAME main.test COMMAND main.test)

endif()