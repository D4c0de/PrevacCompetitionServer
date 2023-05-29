//Verison 1.2.1
//Required version of desktopApp 1.1.0
#include "App.h"
#include <thread>
int main() {
	MainApp::App *Application=new MainApp::App();
	std::thread serverThread(MainApp::App::ServerStart,Application->modbus);
	while (Application->Run())
	{

	}
	serverThread.detach();
	delete Application;
}