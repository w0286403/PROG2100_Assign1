#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;
int main() {
    string fileNameIn = "inFile";
    string fileNameOut = "outFile";
    string line;
    string bufferString;
    string lessThanString = "&lt;";
    string greaterThanString = "&gt;";

    cout << "Please place your file inside the \"files\" directory." << endl;
    cout << "Enter the file name you would like to convert to html (e.g. \"inputFile\"):" << endl;
    //getline(cin,fileNameIn);
    ifstream inputFile("../files/" + fileNameIn + ".cpp");
    if (inputFile.fail()){
        cout << "ERROR - Could not open file " << fileNameIn << endl;
        cout << "Please make sure it is a .cpp file." << endl;
    }

    cout << "Enter the file name for the output (e.g. \"outputFile\")" << endl;
    //getline(cin,fileNameOut);
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

/*
 *TODO
 * Create regex for valid windows filenames
 * Ask about interface
 * Create a custom routine with library string functions (ie find a way to use string.repalce())
 * Implement fin.fail, fout.fail
 * 3 try catch blocks around all file read write and close. PROVIDE EXAMPLES OF LIBRARY, DEFAULT, & PROGRAMMER CREATED EXCEPTIONS
 */
