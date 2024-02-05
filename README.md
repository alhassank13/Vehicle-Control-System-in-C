# Vehicle-Control-System-in-C
A C programming project implementing a Vehicle Control System. Users can turn on/off the engine, set sensors, and control AC and engine temperature. Bonus feature with conditional compilation for Engine Temperature Controller.

## Project Specifications

1.  **User Interaction:**
    
    -   Turn on the vehicle engine
    -   Turn off the vehicle engine
    -   Quit the system
2.  **System State Display:**
    
    -   Print the system state after each user action
3.  **Sensor Readings Menu:**
    
    -   Display a menu for setting sensor readings while the engine is ON
        -   Turn off the engine
        -   Set traffic light color
        -   Set room temperature (Temperature Sensor)
        -   Set engine temperature (Engine Temperature Sensor)
4.  **Sensor-Based Actions:**
    
    -   Adjust vehicle speed based on traffic light data
    -   Control AC and set room temperature based on room temperature data
    -   Control "Engine Temperature Controller" based on engine temperature data
    -   Display current vehicle state after applying sensor-based actions
5.  **Bonus Requirement:**
    -   Use a preprocessor directive (`#define WITH_ENGINE_TEMP_CONTROLLER`) to enable/disable code related to the "Engine Temperature Controller" based on compilation settings.
