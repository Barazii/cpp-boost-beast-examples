add_executable(http-client http_client_ssl.cpp)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)  # Add this line

target_link_libraries(http-client
    ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES}
)
target_include_directories(http-client SYSTEM
    PRIVATE ${OPENSSL_INCLUDE_DIR}
    PRIVATE ${Boost_INCLUDE_DIRS}
)
