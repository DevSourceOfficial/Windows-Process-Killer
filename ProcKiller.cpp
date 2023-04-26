/*
							Software:			Windows Process Killer
							Author:				Gage Morgan / DevSourceOfficial
							Date:				4/25/2023
							Time Started:		8:23PM
							Time Finished:		8:36PM
*/

#include <Windows.h>
#include <iostream>
#include <string>

int main()
{
	// Variables
	HWND hwnd;
	DWORD procId;
	HANDLE hProc;
	UINT exCode;
	std::string windowName;
	BOOL isProcDead;

	// Get the name of the window from the user
	std::cout << "Window title of process you want to kill->: ";
	std::getline(std::cin, windowName);

	// Get the requested exit code from the user
	std::cout << "What code do you want the process to exit with->: ";
	std::cin >> exCode;
	
	// Check to ensure the user entered a window name
	int winNameSize = sizeof(windowName);
	if (winNameSize <= 0)
	{
		std::cout << "No window name inputted...\n";
		Sleep(3000);
		exit(-1);
	}
	std::cout << "Locating window...\n";

	// Attempt to find the window by window title/name
	hwnd = FindWindowA(NULL, windowName.c_str());
	if (hwnd == NULL)
	{
		std::cout << "Unable to find window!\n";
		exit(-1);
	}
	std::cout << "Found window: " << windowName << std::endl;

	// Get the process id of the window
	GetWindowThreadProcessId(hwnd, &procId);
	if (procId == 0)
	{
		std::cout << "Couldnt get process id of " << windowName << std::endl;
		exit(-1);
	}

	// Open the process with terminate privilege
	hProc = OpenProcess(PROCESS_TERMINATE, FALSE, procId);
	if (hProc == NULL)
	{
		std::cout << "Couldn't open process " << windowName << ":" << procId << std::endl;
		exit(-1);
	}
	std::cout << "Proces opened.\n";

	// Attempt to kill the process and store the value in isProcDead so that we can check if the process is dead
	isProcDead = TerminateProcess(hProc, exCode);
	if (!isProcDead)
	{
		std::cout << "Unable to terminate process!\n";
		exit(-1);
	}
	std::cout << "Process terminated..\n";

	// lastly as with most c++ programs we return 0 at the end of int main() function.
	return 0;
}