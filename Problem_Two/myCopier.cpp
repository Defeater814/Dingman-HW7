// Matthew Dingman
// myCopier Script

// This script takes two command line arguments, the first being a file to read
// from, and the second being a file to write to. The script will then proceed
// to open the files and copy line-by-line from the read file into the write
// file.

// Example invocation: ./myCopier file1.txt file2.txt


#include<iostream>
#include<fstream>
#include<cstring>
#include<sstream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) { // If more or less than 2 command line arguments are input, prints error and ends script.
        cout << "Incorrect number of arguments." << endl;
        return 2;
    }
    cout << "The file being read out of is: " << argv[1] << endl; // Prints the file being read from and the file being written to.
    cout << "The file being read to is: " << argv[2] << endl;
    
    fstream readstream;  // Initializes file streams for the two files, and the variable for the line string.
    ofstream writestream;
    string line;

    string read = argv[1]; // Initializes the read and write file names and locations.
    string readFileLoc = "./" + read;

    string write = argv[2];
    string writeFileLoc = "./" + write;

    readstream.open((readFileLoc).c_str(), fstream::in); // Opens both the read and write files.
    writestream.open((writeFileLoc).c_str(), fstream::in);

    if (readstream.is_open() && writestream.is_open()){ // Checks to make sure the files were found and opened properly.
        cout << "Both files successfully opened!" << endl;
    }
    else { // If they aren't found, throws an error and ends script.
        cout << "Error opening files." << endl;
        return 2;
    }
    
    while (readstream.good()) { // Writes line-by-line from the read file into the write file.
        getline(readstream, line);
        writestream << line + "\n";       
    }

    readstream.close(); // Closes both the files when done copying.
    writestream.close();
    
    cout << "Successfully copied text from read file to write file line-by-line." << endl;;
    cout << "End of script." << endl;
    return 0;
}


