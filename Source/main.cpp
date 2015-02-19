// Includes
#include "CBebopInterface.h"
#include "Utility.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>

// Namespaces
using namespace rebop;

void runOnKeyStrokes(CBebopInterface bebop){
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

	// Cleanup - Kill the network and clean up memory
	bebop.Cleanup();
	endwin();
}


void runAutoMode(CBebopInterface bebop) {
	TPilotCommand commandIn;  

	std::cout << "Drone taking off...";
	// Take off
	bebop.Takeoff();

	// Move forward and increase height
	sleep(2);
/*	std::cout << "HEIGHT UP";
	commandIn.flag = 1;
	commandIn.roll = 0;
	commandIn.pitch = 15;
	commandIn.yaw = 0;
	commandIn.gaz = 15;
	commandIn.psi = 0;
	bebop.SendPilotCommand(commandIn);
*/
	// wait for 5 seconds
	sleep(1);

	//Set camera angle
	bebop.setCameraAngle(-100);
	sleep(1);
	//Take picture
	bebop.takePicture(0);

	// Move forward 
	sleep(1);
	for(int i=0;i<40;i++) {
		usleep(60000);
		usleep(60000);
		std::cout << "Move forward";
		usleep(60000);
		usleep(60000);
		commandIn.flag = 1;
		commandIn.roll = 0;
		commandIn.pitch = 30;
		commandIn.yaw = 0;
		commandIn.gaz = 0;
		commandIn.psi = 0;
		bebop.SendPilotCommand(commandIn);
	}
	sleep(2);
	//Take picture
	bebop.takePicture(0);
/*
	// Move forward 
	sleep(1);
	for(int i=0;i<10;i++) {
		sleep(1);
		std::cout << "Move forward";
		commandIn.flag = 1;
		commandIn.roll = 0;
		commandIn.pitch = 15;
		commandIn.yaw = 0;
		commandIn.gaz = 0;
		commandIn.psi = 0;
		bebop.SendPilotCommand(commandIn);
	}*/
	//Land
	sleep(2);
	std::cout << "Drone Landing...";
	bebop.Land();
}

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
		//bebop.FlatTrim();
		runAutoMode(bebop);		
		runOnKeyStrokes(bebop);
	}
	// Cleanup - Kill the network and clean up memory
	bebop.Cleanup();
	endwin();

/*
	std::cout << "Started...";
	sleep(10);
	std::cout << "Stop...";
*/
	return 0;
}
