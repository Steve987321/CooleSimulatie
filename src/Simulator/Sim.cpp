#include "pch.h"
#include "sim.h"

namespace sim
{

bool Application::init()
{
	log_Debug("init");
	
	return true;
}
void Application::run()
{
	log_Debug("debug");
	log_Ok("ok");
	log_Warn("warning");
	log_Error("error");

}
void Application::clean_up()
{
	log_Debug("clean up");
}

}