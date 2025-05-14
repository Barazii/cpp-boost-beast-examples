add_executable(client client.cpp)
add_executable(server server.cpp)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)  # Add this line

target_link_libraries(client
    ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES}
)
target_link_libraries(server
    ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES}
)

target_include_directories(client
    PRIVATE ${OPENSSL_INCLUDE_DIR}
    PRIVATE ${Boost_INCLUDE_DIRS}
)
target_include_directories(server
    PRIVATE ${OPENSSL_INCLUDE_DIR}
    PRIVATE ${Boost_INCLUDE_DIRS}
)