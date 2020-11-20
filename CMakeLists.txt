cmake_minimum_required(VERSION 3.5)

# Set the project name
project (protobuf_dll)

# config
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set (PROTOBUF_FILES ${CMAKE_CURRENT_SOURCE_DIR}/proto)
set (PROTOBUF_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/proto)

# configure protobuf
find_package(Protobuf REQUIRED)
if (!PROTOBUF_FOUND)
    message (FATAL_ERROR "Cannot find Protobuf")
endif()
set(PROTO_SRCS "")
set(PROTO_HDRS "")

file (MAKE_DIRECTORY ${PROTOBUF_OUTPUT})
file (MAKE_DIRECTORY ${PROTOBUF_OUTPUT}/core)
file (MAKE_DIRECTORY ${PROTOBUF_OUTPUT}/dto)

message ("Generating Protobuf CPP files from messages")
file (GLOB EACH_FILE "${PROTOBUF_FILES}/*.proto")
foreach (PROTO_FILE ${EACH_FILE})
    file (TO_NATIVE_PATH ${PROTO_FILE} PROTO_NATIVE_FILE)
    get_filename_component(PROTO_FILENAME ${PROTO_NATIVE_FILE} NAME_WE)
    execute_process (COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} --proto_path=${PROTOBUF_FILES} --cpp_out=${PROTOBUF_OUTPUT}/core ${PROTO_NATIVE_FILE} RESULT_VARIABLE rv)
    if (${rv})
         message(FATAL_ERROR "Generation of data model returned ${rv} for proto ${PROTO_NATIVE_FILE}")
    endif()
    execute_process (COMMAND python3 -m pbtools generate_c_source "${PROTO_NATIVE_FILE}" -o "${PROTOBUF_OUTPUT}/dto")
endforeach (PROTO_FILE)

# organize sources / headers
file (GLOB_RECURSE EACH_FILE "${PROTOBUF_OUTPUT}/*.cc")
foreach (C_FILE ${EACH_FILE})
    file (TO_NATIVE_PATH ${C_FILE} C_NATIVE_FILE)
    list(APPEND PROTO_SRCS "${C_NATIVE_FILE}")
endforeach (C_FILE)

file (GLOB_RECURSE EACH_FILE "${PROTOBUF_OUTPUT}/*.h")
foreach (C_FILE ${EACH_FILE})
    file (TO_NATIVE_PATH ${C_FILE} C_NATIVE_FILE)
    list(APPEND PROTO_HDRS "${C_NATIVE_FILE}")
endforeach (C_FILE)

message ("Protobuf generated sources = ${PROTO_SRCS}")
message ("Protobuf generated headers = ${PROTO_HDRS}")

## ------------------------------------------
# Add an executable
add_executable(protobuf_dll
    src/main.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS}
)

target_include_directories(protobuf_dll
    PUBLIC
    ${PROTOBUF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# link the exe against the libraries
target_link_libraries(protobuf_dll
    PUBLIC
    ${PROTOBUF_LIBRARIES}
)
