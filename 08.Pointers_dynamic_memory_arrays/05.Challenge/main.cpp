/*
    . Testing the ground with the ftxui library.
        . This is a simple example that creates a GUI with three buttons and a progress bar.
        . The buttons increment the progress bar by different amounts when clicked.
        . ftxui is a C++ library for creating terminal user interfaces with a functional and declarative API.
        . This example code works both on Windows and Linux (GCC, Clang).
    . NOTE: 
        . This example won't work in containers because they don't have a xserver
            set up. It's possible to set up one but we'll pass for this course.
        . You can run it: 
            . On a local box with the requirements met: 
                . a compiler with support for modules with cmake:   
                    . gcc 14 and up
                    . clang 16 and up
                    . latest visual c++
        . Be carefult about the opengl dependencies that vcpkg will complain about in the output .
            Install them: apt-get install libx11-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev libgl1-mesa-dev
        . Note that even if we don't have access to xserver we can still build the 
            binary successfuly. We simply can't run it and see a GUI.
        . In this course, we will run it on windows 

*/
import utilities;
import utilities1;

int main()
{

    //it_1::app();
    it_2::app();

    return 0;   
}