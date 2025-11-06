cmake_minimum_required(VERSION 3.16)
project(HanoyTowers)

set(CMAKE_CXX_STANDARD 17)

# Source files
set(SOURCES
    main.cpp
    game.cpp
    tower.cpp
)

# Headers
set(HEADERS
    game.h
    tower.h
    colors.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Windows-specific settings
if(WIN32)
    # Link Windows libraries
    target_link_libraries(${PROJECT_NAME} user32 gdi32 kernel32)
    # Set Windows subsystem
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Cross-compilation settings for MinGW-w64 on macOS
if(CMAKE_CROSSCOMPILING AND CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Static linking for standalone executable
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    
    # Link Windows libraries
    target_link_libraries(${PROJECT_NAME} user32 gdi32 kernel32)
    
    # Set Windows subsystem
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
