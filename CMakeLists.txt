include_directories(include)
file(GLOB sources src/*.c*)

find_package(SFML 2.5 REQUIRED system window audio graphics)

find_package(Threads REQUIRED)

add_executable(run.out ${sources})

target_link_libraries(run.out pthread sfml-system sfml-window sfml-audio
  sfml-graphics)
