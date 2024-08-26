#aux_source_directory(. SRC_LIST)   #当前目录下所有文件名字全部放入SRC_LIST
set(SRC_LIST 
    mprpcapplication.cc 
    mprpcconfig.cc 
    rpcheader.pb.cc 
    rpcprovider.cc 
    mprpcchannel.cc
    mprpccontroller.cc
    logger.cc
    zookeeperutil.cc)
add_library(mprpc ${SRC_LIST})      #创建一个包含这些文件列表的库文件
target_link_libraries(mprpc muduo_net muduo_base pthread zookeeper_mt)