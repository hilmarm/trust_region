add_library(TrustLib
        model.cpp
        polynomial.cpp)


find_package(Qt5Core REQUIRED)
target_link_libraries(TrustLib
        Qt5::Core)