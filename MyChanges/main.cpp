// Includes
#include "CBebopInterface.h"
#include "Utility.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

// Namespaces
using namespace rebop;

int main()
{
	CBebopInterface bebop;

	// Initialize
	bebop.Initialize();

	// Connected and ready to do stuff, theoretically
	if( bebop.IsConnected() == false )
	{
		LOG( ERROR ) << "No connection! Can't do anything!";
	}
	else
	{
		LOG( ERROR ) << "Ready to do stuff!";

		//std::string temp;
		//LOG( INFO ) << "Enter anything to take off.";
		//std::cin >> temp;

		// Take off
//		bebop.takePicture();
	int indexCtr = 0;
	bool flag = true;
	char key;
	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	echo();
	TPilotCommand commandIn;  
        while (flag)
        {
            key = getch();
            
            if ((key == 27) || (key =='q'))
            {
		std::cout << "terminating...";
		std::cout << key;
		//LOG( INFO ) << "Enter anything to land.";
		//std::cin >> temp;

		// Land
		bebop.Land();

		flag = false;
            }
            else if(key == 'a')
            {
		std::cout << "LEFT";
		
			commandIn.flag = 0;
			commandIn.roll = 0;
			commandIn.pitch = 0;
			commandIn.yaw = 15;
			commandIn.gaz = 0;
			commandIn.psi = 0;
		bebop.SendPilotCommand(commandIn);
            }
            else if(key == 'x')
            {
		std::cout << "DOWN";
		// Land
		bebop.Land();
            }
            else if(key == 'w')
            {
		std::cout << "UP";
		// Take off
		bebop.Takeoff();
            }
            else if(key == 'd')
            {
		std::cout << "RIGHT";
			commandIn.flag = 0;
			commandIn.roll = 0;
			commandIn.pitch = 0;
			commandIn.yaw = -15;
			commandIn.gaz = 0;
			commandIn.psi = 0;
		bebop.SendPilotCommand(commandIn);
            }
            else if(key == 's')
            {
		std::cout << "CENTER";
			commandIn.flag = 0;
			commandIn.roll = 0;
			commandIn.pitch = 0;
			commandIn.yaw = 0;
			commandIn.gaz = 0;
			commandIn.psi = 0;
		bebop.SendPilotCommand(commandIn);
            }
            else if(key == 'u')
            {
		std::cout << "PITCH UP";
			commandIn.flag = 1;
			commandIn.roll = 0;
			commandIn.pitch = 15;
			commandIn.yaw = 0;
			commandIn.gaz = 0;
			commandIn.psi = 0;
		bebop.SendPilotCommand(commandIn);
            }
            else if(key == 'n')
            {
		std::cout << "PITCH DOWN";
			commandIn.flag = 1;
			commandIn.roll = 0;
			commandIn.pitch = -15;
			commandIn.yaw = 0;
			commandIn.gaz = 0;
			commandIn.psi = 0;
		bebop.SendPilotCommand(commandIn);
            }

            else if(key == 't')
            {
		std::cout << "HEIGHT UP";
			commandIn.flag = 1;
			commandIn.roll = 0;
			commandIn.pitch = 15;
			commandIn.yaw = 0;
			commandIn.gaz = 15;
			commandIn.psi = 0;
		bebop.SendPilotCommand(commandIn);
            }
            else if(key == 'g')
            {
		std::cout << "HEIGHT DOWN";
			commandIn.flag = 1;
			commandIn.roll = 0;
			commandIn.pitch = -15;
			commandIn.yaw = 0;
			commandIn.gaz = -15;
			commandIn.psi = 0;
		bebop.SendPilotCommand(commandIn);
            }

            else if(key == 'h')
            {
		std::cout << "ROLL LEFT";
			commandIn.flag = 1;
			commandIn.roll = 15;
			commandIn.pitch = 0;
			commandIn.yaw = 0;
			commandIn.gaz = 0;
			commandIn.psi = 0;
		bebop.SendPilotCommand(commandIn);
            }
            else if(key == 'j')
            {
		std::cout << "ROLL RIGHT";
			commandIn.flag = 1;
			commandIn.roll = -15;
			commandIn.pitch = 0;
			commandIn.yaw = 0;
			commandIn.gaz = 0;
			commandIn.psi = 0;
		bebop.SendPilotCommand(commandIn);
            }
            else if(key == 'p')
            {		
		bebop.takePicture(0);
            } 
            else if(key == 'o')
            {		
		bebop.setCameraAngle(90);
            } 
            else if(key == 'i')
            {		
		bebop.setCameraAngle(-90);
            } 
            else if(key == 'm')
            {		
		bebop.setCameraAngle(45);
            } 
            else
            {
		std::cout << key;
            }
	std::cout << "\n";
	}
	}


	// Cleanup - Kill the network and clean up memory
	bebop.Cleanup();
	endwin();
	return 0;
}
