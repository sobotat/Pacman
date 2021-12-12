cmake_minimum_required(VERSION 3.4)
project(pacman)

# use address sanitizer to find memory problems
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")

find_package(SDL2)
if (SDL2_FOUND)
    message("SDL2 FOUND")
    add_executable(pacman main.c src/sdl_playground.c src/draw.c src/entity.c src/level.c src/api.c src/ai.c src/game.c)    

    target_include_directories(pacman PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

    target_include_directories(pacman PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib)    

    target_link_libraries(pacman ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} SDL2_image SDL2_ttf m)

    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  
endif()