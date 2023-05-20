//Verison 1.1.0
//Required version of desktopApp 1.0.1
#include "App.h"

int main() {
	MainApp::App *Application=new MainApp::App();
	while (Application->run())
	{

	}
	delete Application;
}