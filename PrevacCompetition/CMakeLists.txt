cmake_minimum_required(VERSION 3.12)
project(PrevacCompetition)

set(CMAKE_CXX_STANDARD 14)

# Dodaj źródła do projektu
set(SOURCE_FILES
        libmodbus/modbus-data.c
        libmodbus/modbus-rtu.c
        libmodbus/modbus-tcp.c
        libmodbus/modbus.c
        rasberyPi/App.cpp
        rasberyPi/connect.cpp
        rasberyPi/ConveyorBelt.cpp
        rasberyPi/FileOperation.cpp
        rasberyPi/main.cpp
        rasberyPi/Piece.cpp
)

# Dodaj pliki nagłówkowe do projektu
set(HEADER_FILES
        libmodbus/config.h
        libmodbus/modbus-private.h
        libmodbus/modbus-rtu-private.h
        libmodbus/modbus-rtu.h
        libmodbus/modbus-tcp-private.h
        libmodbus/modbus-tcp.h
        libmodbus/modbus-version.h
        libmodbus/modbus.h
        rasberyPi/App.h
        rasberyPi/connect.h
        rasberyPi/ConveyorBelt.h
        rasberyPi/FileOperation.h
        rasberyPi/input.h
        rasberyPi/Piece.h
)

# Dodaj plik zasobów
set(RESOURCE_FILE
       # modbus.rc
)

# Dodaj wykonywalny plik
add_executable(PrevacCompetition ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCE_FILE})
target_link_libraries(PrevacCompetition modbus)
