// zmq_projects.cpp: 定义应用程序的入口点。
//

#include "zmq_projects.h"
#include "include/zmq.h"
#include <Windows.h>
using namespace std;

int main(int argc, char* argv[])
{
	//cout << "Hello CMake." << endl;
	//int major, minor, patch;
	//zmq_version(&major, &minor, &patch);
	//cout << major << " " << minor << " " << patch << endl;


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
