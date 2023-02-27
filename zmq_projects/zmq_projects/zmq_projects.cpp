// zmq_projects.cpp: 定义应用程序的入口点。
//

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
