
//Verison 1.1.1
//Required version of desktopApp 1.0.2

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