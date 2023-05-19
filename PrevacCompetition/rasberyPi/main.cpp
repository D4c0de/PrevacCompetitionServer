
#include "App.h"

int main() {
	MainApp::App *Application=new MainApp::App();
	while (Application->run())
	{

	}
	delete Application;
}