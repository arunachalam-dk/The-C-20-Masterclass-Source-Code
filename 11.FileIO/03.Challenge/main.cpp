/*
    . Contact manager application using ftxui
        . adding contacts
        . deleting contacts
        . listing contacts
        . persisting contacts to a file
            . can read and write contacts to a file

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
int main(int argc, char* argv[])
{
    it_1::app();
}