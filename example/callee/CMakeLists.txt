# set(SRC_LIST userservice.cc ../user.pb.cc)
set(SRC_LIST friendservice.cc ../friend.pb.cc)

add_executable(provider ${SRC_LIST})        #通过这些文件创建可执行文件
target_link_libraries(provider mprpc protobuf)