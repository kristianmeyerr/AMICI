find_package(Git)
if(Git_FOUND)
    execute_process(COMMAND sh -c "${GIT_EXECUTABLE} describe --abbrev=4 --dirty=-dirty --always --tags  | cut -c 2- | tr -d '\n' | sed -E s/-/./"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE PROJECT_VERSION_GIT
        )
endif()

execute_process(COMMAND sh -c "cat version.txt"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE PROJECT_VERSION
    )
