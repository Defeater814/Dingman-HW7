/** Simple On-board LED flashing program - written in C++ by Derek Molloy
*    simple functional struture for the Exploring BeagleBone book
*
*    This program uses USR LED 3 and can be executed in three ways:
*         makeLED on
*         makeLED off
*         makeLED flash  (flash at 100ms intervals - on 50ms/off 50ms)
*         makeLED status (get the trigger status)
*
* * Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

// Matthew Dingman
// makeLED-hw7 program

// This program allows manipulation of LED3 on the BeagleBone Black. It allows
// you to turn the LED on, turn it off, flash the LED, and blink the LED a
// specific amount of times. This script takes one to two command line arguments
// depending on which commands you choose to use. The first argument is the
// the function that you want to LED to do, and the second command line argument
// is how many times you want to blink the LED after using the blink function.

// Example invocations: ./makeLED-hw7 blink 5
//                      ./makeLED-hw7 on

#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
using namespace std;

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(string filename, string value){
   fstream fs;
   string path(LED3_PATH);
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}

void removeTrigger(){
  writeLED("/trigger", "none");
}

int main(int argc, char* argv[]){
   if(argc > 3){
	cout << "Usage is makeLED and one of: " << endl;
        cout << "   on, off, flash or status" << endl;
	cout << " e.g. makeLED flash" << endl;
        return 2;
   }
   string cmd(argv[1]);
   cout << "Starting the makeLED program" << endl;
   cout << "The current LED Path is: " << LED3_PATH << endl;

   // select whether command is on, off, flash or status
   if(cmd=="on"){
        cout << "Turning the LED on" << endl;
	removeTrigger();
        writeLED("/brightness", "1");
   }
   else if (cmd=="off"){
        cout << "Turning the LED off" << endl;
	removeTrigger();
        writeLED("/brightness", "0");
   }
   else if (cmd=="flash"){
        cout << "Flashing the LED" << endl;
        writeLED("/trigger", "timer");
        writeLED("/delay_on", "50");
        writeLED("/delay_off", "50");
   }
   else if (cmd=="status"){
	// display the current trigger details
        std::fstream fs;
	fs.open( LED3_PATH "/trigger", std::fstream::in);
	string line;
	while(getline(fs,line)) cout << line << endl;
	fs.close();
   }
   else if (cmd=="blink"){
   // blinks the LED n amount of times
      if (argc==2) {
          cout << "No blink iteration specified." << endl;
          cout << "Specification should be made after selecting command." <<
          endl;
          cout << "Example invocation: ./makeLED-hw7 blink 5" << endl;
          return 3;
      }
      else{
          int n = atoi(argv[2]);
          removeTrigger();
          cout << "Blinking the LED " << stoi(argv[2]) << " times!" << endl;
          for (int i = 0; i < n; i++) {
              writeLED("/brightness", "1");
              sleep(1);
              writeLED("/brightness", "0");
              sleep(1);
          }
      }
   }
   else{
	cout << "Invalid command!" << endl;
   }
   cout << "Finished the makeLED Program" << endl;
   return 0;
}
