add_executable(http-client-with-ssl http_client_ssl.cpp)
add_executable(http-client-without-ssl http_client_no_ssl.cpp)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)  # Add this line

target_link_libraries(http-client-with-ssl
    ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES}
)
target_link_libraries(http-client-without-ssl
    ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES}
)

target_include_directories(http-client-with-ssl SYSTEM
    PRIVATE ${OPENSSL_INCLUDE_DIR}
    PRIVATE ${Boost_INCLUDE_DIRS}
)
target_include_directories(http-client-without-ssl SYSTEM
    PRIVATE ${OPENSSL_INCLUDE_DIR}
    PRIVATE ${Boost_INCLUDE_DIRS}
)