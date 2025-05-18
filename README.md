# controller_homework
This code reads xbox controller inputs and displays them in a Qt console application 

I am using Qt Creator Version 16.02, based on Qt 6.8.3
My host is debian based. I am running PopOS version 22.04 LTS (It is essentially Ubuintu without Snap D)

I had to install joystick to make the code work {sudo apt install joystick}

The main.cpp file has a main function and read_joystick function. I included QDebug so button press and axis values could be displayed in the application output window.
