if(LINUX_SYSTEM)
    list(APPEND OS_FILES
    Linux/UDPClientConnection.hpp
    Linux/UDPClientConnection.cpp
    )
endif()

if(WINDOWS_SYSTEM)
    list(APPEND OS_FILES
    Windows/UDPClientConnection.hpp
    Windows/UDPClientConnection.cpp
    )
endif()

add_library(Logger
Logger.cpp
Logger.hpp
${OS_FILES}
)

if(LOG_ENABLED)
add_compile_definitions(LOG_ENABLED)
endif()
