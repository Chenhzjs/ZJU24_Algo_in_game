cmake_minimum_required(VERSION 3.10)

project(SlayTheSpire)

set(CMAKE_C_STANDARD 11)

include_directories(include)

set(SOURCES
    main.c
    battle.c
    card.c
    character.c
    draw.c
    interface.c
    libgraphics/exceptio.c
    libgraphics/genlib.c
    libgraphics/graphics.c
    libgraphics/random.c
    libgraphics/simpio.c
    libgraphics/strlib.c
)

set(HEADERS
    battle.h
    card.h
    character.h
    draw.h
    interface.h
    include/exception.h
    include/extgraph.h
    include/gcalloc.h
    include/genlib.h
    include/graphics.h
    include/random.h
    include/simpio.h
    include/strlib.h
)

add_executable(main ${SOURCES} ${HEADERS})

target_compile_options(main PRIVATE -Wall -Wextra -O2)
