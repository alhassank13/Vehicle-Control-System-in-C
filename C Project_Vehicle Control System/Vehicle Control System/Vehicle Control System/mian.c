/*
===================================================================================
Name	    : Mini_Project1
Author      : ALHassan Khaled
Description : Vehicle Control System
Date        : DEC 22 2023
===================================================================================
 */


#include <stdio.h>

/***Options to show Engine Temperature
 *	Choose: Show		1
 *			NOT Show 	0
 */

#define WITH_ENGINE_TEMP_CONTROLLER												0


//Initial Values for StateMenu_1 Structure
#define Engine_State_Initial													0	// Initial state of the engine (OFF)
#define AC_State_Initial 														0	// Initial state of the air conditioning (OFF)
#define Vehicle_Speed_State_Initial 											95	// Initial vehicle speed set to 95 km/hr
#define Room_Temperature_State_Initial 										    25	// Initial room temperature set to 25°C
#if WITH_ENGINE_TEMP_CONTROLLER == 1
#define Engine_Temperature_Controller_State_Initial							 	0	// Initial state of the engine temperature controller (OFF)
#define Engine_Temperature_State_Initial 										90	// Initial engine temperature set to 90°C
#endif


// Initialize a boolean data type using an enumeration
typedef enum {
	OFF = 0, // Represents the logical state "OFF" or "false"
	ON  = 1  // Represents the logical state "ON" or "true"
} bool;

//Initialize a start menu structure
typedef struct{
	bool Engine_State;	    					// Initialize a boolean variable
	bool AC_State;								// Initialize a boolean variable
	int Vehicle_Speed_State;					// Variable for vehicle speed
	int Room_Temperature_State; 				// Variable for room temperature
#if WITH_ENGINE_TEMP_CONTROLLER == 1
	bool Engine_Temperature_Controller_State;	// Variable for engine temperature controller state
	int Engine_Temperature_State;				// Variable for engine temperature
#endif
}StateMenu_t;




// Initialize an instance of the StateMenu_t structure with specific initial values
StateMenu_t StateMenu_1 = {
		Engine_State_Initial,                     		// Initial state of the engine
		AC_State_Initial,                          		// Initial state of the air conditioning
		Vehicle_Speed_State_Initial,               		// Initial speed of the vehicle
		Room_Temperature_State_Initial,            		// Initial room temperature
#if WITH_ENGINE_TEMP_CONTROLLER == 1
		Engine_Temperature_Controller_State_Initial, 	// Initial state of the engine temperature controller, included if WITH_ENGINE_TEMP_CONTROLLER is defined as 1
		Engine_Temperature_State_Initial          		// Initial engine temperature
#endif
};

//StateMenu_t StateMenu_1={OFF,OFF,95,25,OFF,90};

// Pointer to the StateMenu_t object
StateMenu_t *StateMenu_ptr= &StateMenu_1;


// Function prototypes for the vehicle control system

// Display the main menu to the user
void MainMeun(void);

// Perform actions based on the user's input in the main menu
void MainMenuAction(char Manimenu);

// Determine speed based on traffic light color and update the system state
void TrafficLightColor(char color, StateMenu_t *StateMenu_2);

// Display options for the sensors set menu
void SensorsSetMenu(void);

// Perform actions based on the user's input in the sensors set menu
void SensorsSetMenuAction(char Sensorset);

// Display the current state of the vehicle system
void CurrentVehicleStateMenu(StateMenu_t *StateMenu_2);

// Update the system state based on room temperature input
void Room_Temperature_Data(int Temp, StateMenu_t *StateMenu_2);

#if WITH_ENGINE_TEMP_CONTROLLER == 1
// Update the system state based on engine temperature input
void Engine_Temperature(int Temp, StateMenu_t *StateMenu_2);
#endif


/******************************* START MAIN *******************************/
int main(){

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	//Local Variables
	char input_Char;

	// The following do-while loop continues executing the main menu until the user chooses to quit.

	do {
		// Display the main menu to the user
		MainMeun();
		// Get user input for menu selection
		scanf(" %c", &input_Char);
		// Perform the action corresponding to the user's input
		MainMenuAction(input_Char);
		// Continue the loop as long as the user input is not 'c' or 'C' (quit condition)
	} while ((input_Char != 'c') && (input_Char != 'C'));


	/******************************* END MAIN *******************************/
	return 0;
}


/******************************* Function Implementation *******************************/

// This function displays the main menu options to the user
void MainMeun(void){
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
	printf("Please .. Enter Your Choose: ");
}


void MainMenuAction(char Manimenu){
	char input_SensorsSetMenu;		// Variable to store user input for the sensor menu
	// Use a switch statement to handle different menu options
	switch(Manimenu){
	// Case for turning on the vehicle engine
	case 'a':
	case 'A':
		// Turn on the vehicle engine
		printf(">>> Turn on the vehicle engine <<<\n\n");
		StateMenu_ptr->Engine_State=ON;
		// Display the sensor settings menu and get user input
		SensorsSetMenu();
		scanf(" %c",&input_SensorsSetMenu);
		// Perform actions based on the user's choice in the sensor menu
		SensorsSetMenuAction(input_SensorsSetMenu);
		break;

		// Case for turning off the vehicle engine
	case 'b':
	case 'B':
		// Turn off the vehicle engine
		printf(">>> Turn off the vehicle engine <<<\n\n");
		StateMenu_ptr->Engine_State=OFF;
		break;

		// Case for quitting the system
	case 'c':
	case 'C':
		// Quit the system
		printf(">>> Quit the system <<<\n\n");
		break;
	}
}




void SensorsSetMenu(void){
	// Display options for the sensors set menu
	printf("a. Turn off the vehicle engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature\n");
#if WITH_ENGINE_TEMP_CONTROLLER == 1
	// Display option 'd' to set the engine temperature (conditionally compiled)
	printf("d. Set the engine temperature\n\n");
#endif
	printf("Please .. Enter Your Choose: ");
}


// Perform actions based on the user's input in the sensors set menu
void SensorsSetMenuAction(char Sensorset){
	char input_color;
	int input_RoomTempOREngineTemp;

	// Use a switch statement to handle different options in the sensor set menu
	switch(Sensorset){
	case 'a':
	case 'A':
		// Turn off the vehicle engine
		printf(">>> Turn off the vehicle engine <<<\n\n");
		break;
	case 'b':
	case 'B':
		// Set the traffic light color
		printf(">>> Set the traffic light color <<<\n");
		printf("\n");
		printf("G. Green \n");
		printf("O. Orange \n");
		printf("R. Red \n");
		printf("\n");

		// Prompt the user to enter the required color
		printf("Please .. Enter the required color: ");
		scanf(" %c", &input_color);
		// Call the function to determine speed based on traffic light color
		TrafficLightColor(input_color, StateMenu_ptr);
		printf("\n");
		// Display the current state of the vehicle system
		CurrentVehicleStateMenu(StateMenu_ptr);
		break;
	case 'c':
	case 'C':
		// Set the room temperature
		printf(">>> Set the room temperature <<<\n");
		printf("\n");
		// Prompt the user to enter the room temperature
		printf("Please .. Enter the Room Temp: ");
		scanf("%d", &input_RoomTempOREngineTemp);
		// Call the function to update the system state based on room temperature input
		Room_Temperature_Data(input_RoomTempOREngineTemp, StateMenu_ptr);
		printf("\n");
		// Display the current state of the vehicle system
		CurrentVehicleStateMenu(StateMenu_ptr);
		break;

#if WITH_ENGINE_TEMP_CONTROLLER == 1
	case 'd':
	case 'D':
		// Set the engine temperature
		printf(">>> Set the engine temperature <<<\n");
		printf("\n");
		// Prompt the user to enter the engine temperature
		printf("Please .. Enter the Engine Temp: ");
		scanf("%d", &input_RoomTempOREngineTemp);
		// Call the function to update the system state based on engine temperature input
		Engine_Temperature(input_RoomTempOREngineTemp, StateMenu_ptr);
		printf("\n");
		// Display the current state of the vehicle system
		CurrentVehicleStateMenu(StateMenu_ptr);
		break;
#endif
	}
}

// Function to determine speed based on traffic light color
void TrafficLightColor(char color, StateMenu_t *StateMenu_2) {
	int Vehicle_speed;

	// Use a switch statement to handle different traffic light colors
	switch (color) {
	case 'g':   // If the user chooses GREEN color
	case 'G':
		Vehicle_speed = 100;    // Set the speed of the vehicle to 100 km/hr
		StateMenu_2->Vehicle_Speed_State = Vehicle_speed;
		break;

	case 'o':   // If the user chooses ORANGE color
	case 'O':
		Vehicle_speed = 30; // Set the speed of the vehicle to 30 km/hr
		StateMenu_2->Vehicle_Speed_State = Vehicle_speed;

		// Turn on the AC and adjust room temperature
		StateMenu_2->AC_State = ON;
		StateMenu_2->Room_Temperature_State = StateMenu_2->Room_Temperature_State * (5 / 4) + 1;

		// Conditionally enable engine temperature controller
#if WITH_ENGINE_TEMP_CONTROLLER == 1
		StateMenu_2->Engine_Temperature_Controller_State = ON;

		// Adjust engine temperature
		StateMenu_2->Engine_Temperature_State = StateMenu_2->Engine_Temperature_State * (5 / 4) + 1;
#endif
		break;

	case 'r':   // If the user chooses RED color
	case 'R':
		Vehicle_speed = 0;  // Set the speed of the vehicle to 0 km/hr
		StateMenu_2->Vehicle_Speed_State = Vehicle_speed;
		break;
	}
}

// Function to adjust room temperature based on input
void Room_Temperature_Data(int Temp, StateMenu_t *StateMenu_2) {
    // Check if the input temperature is outside the valid range (10 to 30)
    if ((Temp < 10) || (Temp > 30)) {
        // If outside the range, turn on the AC and set room temperature to 20
        StateMenu_2->AC_State = ON;
        StateMenu_2->Room_Temperature_State = 20;
    } else {
        // If within the range, turn off the AC
        StateMenu_2->AC_State = OFF;
    }
}

#if WITH_ENGINE_TEMP_CONTROLLER == 1
// Function to adjust engine temperature based on input
void Engine_Temperature(int Temp, StateMenu_t *StateMenu_2) {
    // Check if the input temperature is outside the valid range (100 to 150)
    if ((Temp < 100) || (Temp > 150)) {
        // If outside the range, conditionally enable engine temperature controller
        StateMenu_2->Engine_Temperature_Controller_State = ON;

        // Set engine temperature to 125
        StateMenu_2->Engine_Temperature_State = 125;
    } else {
        // If within the range, conditionally disable engine temperature controller
        StateMenu_2->Engine_Temperature_Controller_State = OFF;
    }
}

#endif

// Function to display the current state of the vehicle and take user input for further actions
void CurrentVehicleStateMenu(StateMenu_t *StateMenu_2) {
	char input_Sensors;

	// Display header for the result section
	printf("\n================================\n");
	printf(">>> The Result <<<\n");
	printf("\n");

	// Display Engine state
	if (StateMenu_2->Engine_State == OFF) {
		printf("Engine state is OFF\n");
	} else if (StateMenu_2->Engine_State == ON) {
		printf("Engine state is ON\n");
	}

	// Display AC state
	if (StateMenu_2->AC_State == OFF) {
		printf("AC is OFF\n");
	} else if (StateMenu_2->AC_State == ON) {
		printf("AC is ON\n");
	}

	// Display Vehicle Speed
	printf("Vehicle Speed: %d km/hr\n", StateMenu_2->Vehicle_Speed_State);

	// Display Room Temperature
	printf("Room Temperature: %d°C\n", StateMenu_2->Room_Temperature_State);

#if WITH_ENGINE_TEMP_CONTROLLER == 1
	// Display Engine Temperature Controller State
	if (StateMenu_2->Engine_Temperature_Controller_State == OFF) {
		printf("Engine Temp Controller is OFF\n");
	} else if (StateMenu_2->Engine_Temperature_Controller_State == ON) {
		printf("Engine Temp Controller is ON\n");
	}

	// Display Engine Temperature
	printf("Engine Temperature: %d°C\n", StateMenu_2->Engine_Temperature_State);
#endif

	// Display footer for the result section
	printf("================================\n");
	printf("\n");

	// Display sensor settings menu and get user input for further actions
	SensorsSetMenu();
	scanf(" %c", &input_Sensors);
	SensorsSetMenuAction(input_Sensors);
}
