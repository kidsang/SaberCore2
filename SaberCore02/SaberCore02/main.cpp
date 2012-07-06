#include <Windows.h>
#include "scCore.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
	scCore core("", true);

	core.start();

	return 0;
}