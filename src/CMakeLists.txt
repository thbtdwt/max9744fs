find_package(FUSE REQUIRED)

set(EXE max9744d)

add_compile_options("$<$<CONFIG:RELEASE>:-O2>")
add_compile_options("$<$<CONFIG:DEBUG>:-O0;-g;-DDEBUG_TRACE_ON>")

add_compile_options(-Wall -Werror -Wextra )
add_definitions(-D_FILE_OFFSET_BITS=64)

set(SRC
	MAX9744.c
	sound_fs.c
    main.c
    )

set(CMAKE_INSTALL_PREFIX "/" CACHE PATH "" FORCE)

add_executable(${EXE} ${SRC})
target_link_libraries(${EXE} ${FUSE_LIBRARIES})

install(TARGETS ${EXE} DESTINATION usr/bin)
install(FILES max9744d.service DESTINATION etc/systemd/system)
