#include <QCoreApplication>

//needed to support controller input
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/joystick.h>
#include <sys/ioctl.h>
#include <QDebug>

//This function takes in i/o from the linux host and displays button press and axis values
void read_joystick(){
    //opens the file and reads in like a buffer / file stream
    int joy_fd = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);
    if (joy_fd < 0) {
        perror("Could not open joystick");
    }

    //gets the number of button and axis values
    int num_axes, num_buttons;
    ioctl(joy_fd, JSIOCGAXES, &num_axes);
    ioctl(joy_fd, JSIOCGBUTTONS, &num_buttons);    

    //creates a struct to instantiate event values from the joystick packages installed on host
    struct js_event event;
    while (true) {
        if (read(joy_fd, &event, sizeof(event)) == sizeof(event)) {
            //switch statement based on event read from button press or axis value
            switch (event.type & ~JS_EVENT_INIT) {
            case JS_EVENT_BUTTON:
                qDebug() << "Button number:" << event.number << "Button value:" << event.value;
                break;
            case JS_EVENT_AXIS:
                qDebug() << "Axis number:" << event.number << "Axis value:" << event.value;
                break;
            }
        }
    }
    //closes the stream
    close(joy_fd);
}

//main function calls read_joystick
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    read_joystick();

    return a.exec();
}
