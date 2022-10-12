#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;
bool validate(string);

int main() {
    string fileNameIn = "inFile";
    string fileNameOut = "outFile";
    string line;
    string bufferString;
    string lessThanString = "&lt;";
    string greaterThanString = "&gt;";
    bool willContinue = true;

    cout << "Please place your file inside the \"files\" directory." << endl;
    cout << "Enter the file name you would like to convert to html (e.g. \"inputFile\"):" << endl;
    getline(cin,fileNameIn);
    willContinue = validate(fileNameIn);
    if (!willContinue){
        cout << "ERROR" << endl;
    }
    ifstream inputFile("../files/" + fileNameIn + ".cpp");
    if (inputFile.fail()){
        cout << "ERROR - Could not open file " << fileNameIn << endl;
        cout << "Please make sure it is a .cpp file." << endl;
    }

    cout << "Enter the file name for the output (e.g. \"outputFile\")" << endl;
    getline(cin,fileNameOut);
    ofstream outputFile("../files/" + fileNameOut + ".html",ios::out);
    if (outputFile.fail()){
        cout << "ERROR - Could not open " << fileNameOut << "for output." << endl;
    }


    outputFile << "<PRE>" << endl;

    while(!inputFile.eof()){
        getline(inputFile,line);

        for (char i : line) {
            if (i == '<'){
                bufferString += lessThanString;
            }else if (i == '>'){
                bufferString += greaterThanString;
            }else{
                bufferString += i;
            }
        }

        outputFile << bufferString << endl;
        bufferString.clear();
    }
    outputFile << "</PRE>" << endl;

    inputFile.close();
    outputFile.close();

    cout << "Your file has been converted to HTML! Please check the \"files\" directory." << endl;
    return 0;
}

bool validate(string fileName){
    bool willContinue = true;
    if (regex_match(fileName,regex("CON|PRN|AUX|NUL|COM1|COM2|COM3|COM4|COM5|COM6|COM7"
                                   "|COM8|COM9|LPT1|LPT2|LPT3|LPT4|LPT5|LPT6|LPT7|LPT8|LPT9"))){
        willContinue = false;
    }else if(!regex_match(fileName,regex("[a-zA-Z_]\\s?[a-zA-Z_0-9]*"))){
        willContinue = false;
    }
    //[a-zA-Z_]\s?[a-zA-Z_0-9]*.[a-zA-Z0-9]+ REGEX FOR FILE TYPES

    return willContinue;
}

/*
 *TODO
 * Create regex for valid windows filenames
 * Ask about interface
 * 3 try catch blocks around all file read write and close. PROVIDE EXAMPLES OF LIBRARY, DEFAULT, & PROGRAMMER CREATED EXCEPTIONS
 */
