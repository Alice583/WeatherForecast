add_executable(${PROJECT_NAME} main.cpp ${curses_SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE lib)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

#include_directories(${PROJECT_SOURCE_DIR}/third-party/PDCurses-3.9/pdcurses)

#add_library(curses ${PROJECT_SOURCE_DIR}/third-party/PDCurses-3.9/wincon/pdcurses.a)
#set_target_properties(curses PROPERTIES LINKER_LANGUAGE CXX)

#add_library(curses SHARED ${PROJECT_SOURCE_DIR}/third-party/PDCurses-3.9/wincon/pdcurses.dll)
#set_target_properties(curses PROPERTIES LINKER_LANGUAGE CXX)
#target_link_libraries(${PROJECT_NAME} PRIVATE curses)
#target_link_libraries(${PROJECT_NAME} PRIVATE -lcurses)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/libcurl-d.dll
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/libcpr.dll
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${CMAKE_BINARY_DIR}/lib/liblib.dll
#        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

