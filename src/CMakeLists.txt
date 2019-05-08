find_package(FUSE REQUIRED)

set(SRC
	MAX9744.c
	sound_fs.c
    main.c
    )

add_executable(${EXE} ${SRC})
target_link_libraries(${EXE} ${FUSE_LIBRARIES})