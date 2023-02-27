# ZMQ-

![image](https://user-images.githubusercontent.com/13326017/219828460-8e93ce51-4f61-45d5-b7ad-87e3683bd72b.png)
![image](https://user-images.githubusercontent.com/13326017/219828466-89115bca-6933-44ca-b002-d3359bd9f0de.png)


** 调用libzmq v143版本的第三方库 开始消息中间件 IPC开发之旅 **
CMakeLists.txt的内容
```
cmake_minimum_required(VERSION 3.5)

project(zmq_projects)

# 将源代码添加到此项目的可执行文件。
add_executable (zmq_projects "zmq_projects.cpp" "zmq_projects.h")

add_library(mylib SHARED IMPORTED)
set_target_properties(mylib PROPERTIES
IMPORTED_LOCATION "${CMAKE_INCLUDE_CURRENT_DIR}/dll/libzmq-v143-mt-gd-4_3_5.dll"
IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/libzmq-v143-mt-gd-4_3_5.lib"
INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include")

 file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dll/libzmq-v143-mt-gd-4_3_5.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../out/build/x86-debug/zmq_projects)

target_link_libraries(zmq_projects mylib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET zmq_projects PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
```

libzmq库的存放路径，如图所示。
![image](https://user-images.githubusercontent.com/13326017/221469101-c3f14f70-341f-4e7f-a444-488d2312382f.png)
![image](https://user-images.githubusercontent.com/13326017/221469269-86ed6b0d-bc5a-4ea2-94f6-28413b42b0fd.png)


** 测试能否成功调用 lizmq这个完美消息队列第三库 **
```
#include "zmq_projects.h"
#include "include/zmq.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	int major, minor, patch;
	zmq_version(&major, &minor, &patch);

	cout << major << " " << minor << " " << patch << endl;

	return 0;
}
```
**添加zmq中 sub和pub 发布订阅模式**
```
int main(int argc, char* argv[])
{
	if (argc >= 4 && !strcmp("-sub", argv[2])) // 如果是订阅
	{
		/******************* 订阅 *********************/
		void* context = zmq_ctx_new();
		void* subscriber = zmq_socket(context, ZMQ_SUB);

		if (!strcmp("-server", argv[1])) // 作为服务端
			zmq_bind(subscriber, "tcp://*:12345");
		else if (!strcmp("-client", argv[1])) // 作为客户端
			zmq_connect(subscriber, "tcp://localhost:12345");
		else
		{
			printf("please add true param:\n"
				"for example: \n"
				"-server -sub [topic] [...]\n"
				"-client -sub [topic] [...]\n"
				"-server -pub [topic] [msg]\n"
				"-client -pun [topic] [msg]]n");
			return 0;
		}

		int i = 0;
		for (i = 3; i < argc; ++i)
		{
			zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, argv[i],
				strlen(argv[i]));
			printf("sub topic:%s\n", argv[i]);
		}
		char topic_name[256] = { 0 }; // 订阅主题
		char payload[1024] = { 0 }; // 接收订阅主题的内容
		while (1)
		{
			memset(topic_name, 0, sizeof(topic_name));
			memset(payload, 0, sizeof(payload));

			int size = zmq_recv(subscriber, topic_name, sizeof(topic_name), 0);
			if (size == -1)
			{
				printf("recv topic error！");
			}
			size = zmq_recv(subscriber, payload, sizeof(payload), 0);
			if (size == -1)
			{
				printf("recv payload error!");
			}
			printf("Topic:%s  Msg:%s\n", topic_name, payload);
		}
		zmq_close(subscriber);
		zmq_ctx_destroy(context);
		return 0;
		/**************** end ****************/
	}
	else if (argc == 5 && !strcmp("-pub", argv[2]))
	{
		/************** 发布 *****************/
		void* context = zmq_ctx_new();
		void* publisher = zmq_socket(context, ZMQ_PUB);
		if (!strcmp("-server", argv[1])) // 作服务端
			zmq_bind(publisher, "tcp://*:12345");
		else if (!strcmp("-client", argv[1])) // 作客户端
			zmq_connect(publisher, "tcp://localhost:12345");
		else
		{

			printf("Please add true param:\n"
				"For example:\n"
				"-server -sub [topic1] [...]\n"
				"-client -sub [topic1] [...]\n"
				"-server -pub [topic] [msg]\n"
				"-client -pun [topic] [msg]\n");
			return 0;
		}
		while (1)
		{
			zmq_send(publisher, argv[3], strlen(argv[3]), ZMQ_SNDMORE); //指定要发布消息的主题
			zmq_send(publisher, argv[4], strlen(argv[4]), 0);   //向设置的主题发布消息

			//zmq_send (publisher, "hello", strlen("hello"), ZMQ_SNDMORE); //可发布多个主题的消息
			//zmq_send (publisher, "world", strlen("world"), 0);
			// sleep(1);									//每秒发布一次
			Sleep(1);
		}

		zmq_close(publisher);		//退出时调用
		zmq_ctx_destroy(context);
		return 0;
		/*************************** End  ***************************/
	}
	else
	{
		printf("Please add true param:\n"
			"For example:\n"
			"-server -sub [topic1] [...]\n"
			"-client -sub [topic1] [...]\n"
			"-server -pub [topic] [msg]\n"
			"-client -pun [topic] [msg]\n");
		return 0;
	}
	return 0;
}
```
** 再次发现了VS的强大，对cmake项目右键可以打开shellpower控制台窗口，然后通过终端运行可执行文件exe实例**
![image](https://user-images.githubusercontent.com/13326017/221489200-b74906d8-0ff0-4419-bbd9-e1fa4010b40e.png)
![image](https://user-images.githubusercontent.com/13326017/221489339-54486795-f39a-444e-aa88-111fa7c74eb7.png)



