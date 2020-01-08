#include "AppInstance.h"

AppInstance::AppInstance()
	:_vars()
{
}

EnvVariables& AppInstance::vars()
{
	return _vars;
}
