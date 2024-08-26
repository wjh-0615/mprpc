# mprpc项目
本项目通过muduo网络库，使用protobuf和rpc设计出一个高性能网络通讯框架，用于分布式通信。
### 项目代码工程目录
bin: 可执行文件  
build: 项目编译文件  
lib: 项目库文件  
src: 源文件   src/rpcprovider:提供发布rpc方法的框架底层；src/mprpcchannel:提供调用rpcstub代理的底层代码；src/mprpc/config:读取配置文件
test: 测试代码  
example: 框架代码使用范例  
autobuild.sh: 一键编译脚本  
### 相关配置  
protobuf,Zookeeper,muduo网络库  
### 相关技术实现步骤
1.编写rpc服务提供方，并与ZK建立连接；创建维护rpc方法的map表，提供可以发布rpc方法的函数接口  

2.启动服务节点，注册所有rpc方法在Znode节点上；通过事件循环处理rpc方法请求，其中包括连接和读写事件，读写事件需要对请求参数反序列化，获取相应rpc方法后调用方法并回调；  

3.编写rpc方法请求客户端，描写基于stub代理调用的底层callMethod方法，获取请求参数后基于tcpsocket编程发送请求；获取响应并反序列化；  

4.编写日志系统，为解决日志存储IO过多，将日志消息先写入缓冲消息队列，之后从缓冲队列读取日志消息写入日志文件中；  

5.提供相应使用范例，使用编写框架发布rpc方法，客户端调用rpc方法；其中使用protobuf进行数据的序列化与反序列化，muduo网络库实现通信。  
