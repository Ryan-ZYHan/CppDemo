SET(test_INC   
${PROJECT_SOURCE_DIR}/include
)
INCLUDE_DIRECTORIES(${test_INC})

# 添加libserialport库的路径
set(LIBSERIALPORT_DIR /usr/local/lib/)

file(GLOB_RECURSE TestSRC  
                ../include/FileExtension.cpp
                ../include/Change.cpp
                ../include/Checkout.cpp
                ../include/easylogger/*.c
                ../include/cJSON/*.c
                ./usb2RS485/SerialPort.cpp       

                # ./usb2RS485/main.cpp
                # ./usb2RS485/haibao.cpp
                # ./usb2RS485/hezong.cpp
                # ./CRC/main.cpp
                # ./atomic/main.cpp
                # ./usb2RS485/haibaoTest.cpp
                # ./inherit/main.cpp
                # ./arrayTest/main.cpp
                # ./weld/handle.cpp
                ./weld/Handle.cpp
                # ./socket/readJsonFormIPandPort.cpp
                )

#test
add_executable(testUT ${TestSRC})
# 添加libserialport库的链接
target_link_libraries(testUT pthread stdc++fs event ${LIBSERIALPORT_DIR}/libserialport.so)
enable_testing()