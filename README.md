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


