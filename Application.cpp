/** this example is in the public domain **/
/** author: Sébastien Boisvert **/

#include "Application.h"
#include "TestPlugin.h"

Application::Application(int argc,char**argv){
}

void Application::run(){

	TestPlugin plugin;
	getCore()->registerPlugin(&plugin);

	getCore()->run();
}
