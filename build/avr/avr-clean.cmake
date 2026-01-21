get_filename_component(ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

file(REMOVE_RECURSE
    "${ROOT_DIR}/build/avr"
    "${ROOT_DIR}/build/vs/avr"
)
