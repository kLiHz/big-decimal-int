project(Big-Decimal-Int)

set(CMAKE_CXX_STANDARD 14)

add_library(BigInt INTERFACE BigInt.hpp)

add_executable(1 1.cpp)
target_link_libraries(1 BigInt)

add_executable(2 2.cpp)
target_link_libraries(2 BigInt)

add_executable(3 3.cpp)
target_link_libraries(3 BigInt)

add_executable(4 4.cpp)
target_link_libraries(4 BigInt)
