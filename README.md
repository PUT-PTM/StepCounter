# StepCounter
### Overview
The Step Counter is built on STM32. It is used for counting steps.
### Description
While walking, the human body moves vertically in a specific way, slightly bouncing. We use an accelerometer to analyze the changes of it's posision in space. By studying the nature of those changes, we are able to specify particular steps out of it and count them. The number of counted steps will be displayed on a digital screen.
### Tools
* STM32F4DISCOVERY microcontroller
* LIS3DSH accelerometer (built-in)
* DSP Library
* 4-digit display
* Powerbank Reinston 5000
### How to run
Software: System WorkBench for STM32 based on Eclipse

| STM32               | TM1637 LED Display
| ------------------- |:-----------------:
| GDN                 | GND 
| 5V                  | VCC
| PC0                 | CLK
| PC1                 | DI0


Plug STM32 to the Powerbank Reinston 5000
### How to compile
Open the project in SystemWorkbench based on Eclipse. Make sure you added the DSP Library properly. Connect your Microntroller to USB port and run the project.
### Future improvements
The data provided by the accelerometer is not the very best base for counting steps due to it's slight inaccuracy. That is why sometimes the Step Counter miscounts and displays one or two steps more/less. Future upgrades might apply:
* converting steps to distance
* calculating calories
* recognising the difference between walking and running
### Credits
The autors are: [Paweł Januzik](https://github.com/paweljanpawel) and [Maciej Łaszkiewicz](https://github.com/MaciejunioYJB)

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.

Supervisor: **Tomasz Mańkowski**
