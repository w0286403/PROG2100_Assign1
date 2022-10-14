#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <stdexcept>
using namespace std;
void validate(string); // P Declaration for validate

struct fileException : public exception{ //Create file handling exception that will accept a message depending on scenario
public:
    string message;
    fileException(string messageIn){
        this->message = messageIn;
    }
    const string what(){
        return "File has failed. " + message;
    }
};

int main() {
    //PATH = E:\ITProgrammingFall2022\PROG\Assignment1\files\inFile
    string fileNameIn;// = "inFile";
    string fileNameOut;// = "outFile";
    ifstream inputFile;
    ofstream outputFile;
    string currentLine;
    string bufferLine;
    string lesserThanString = "&lt;";
    string greaterThanString = "&gt;";
    bool willContinue = false;

    cout << "\nFILE CONVERTER cpp -> html\n" << endl;
    cout << "Please make sure your file path includes a drive letter. Please do not include the file type.\n" << endl;

    do {
        try {//Try to grab filenames, validate against regex, and open
            cout << R"(Enter the path to the file you would like to convert to html. (e.g. C:\files\inputFile):)" << endl;
            getline(cin,fileNameIn);
            validate(fileNameIn);
            inputFile.open(fileNameIn + ".cpp");
            if (inputFile.fail()){ //If files fail, throw exception
                throw fileException("Please check spelling and make sure it is a cpp file.");
            }

            cout << R"(Enter the path and name for the output html file. (e.g. C:\files\outputFile))" << endl;
            getline(cin,fileNameOut);
            validate(fileNameOut);
            outputFile.open(fileNameOut + ".html",ios::out);
            if (outputFile.fail()){
                throw fileException("An error occurred with the output file.");
            }
            willContinue = true;
        }catch (const invalid_argument& ex) {//Invalid argument through validate function
            cout << ex.what() << endl;
        }catch (fileException& ex){
            cout << ex.what() << endl;
        }catch (...){
            cout << "An unexpected error has occurred." << endl;
        }
    }while(!willContinue);

    try{//Try-catch for reading through input line
        outputFile << "<PRE>" << endl;

        while(!inputFile.eof()){ //While there is data in file, read dit line by line
            if (!getline(inputFile, currentLine)){
                throw fileException("");
            }else {
                for (char i: currentLine) { //For each character in the line, check if it is < or >
                    //Replace where applicable and append to buffer string
                    if (i == '<') {
                        bufferLine += lesserThanString;
                    } else if (i == '>') {
                        bufferLine += greaterThanString;
                    } else {
                        bufferLine += i;
                    }
                }

                outputFile << bufferLine << endl;//write buffer string to outputfile
                bufferLine.clear();//clear the string to read new line
            }
        }
        outputFile << "</PRE>" << endl;

        inputFile.close();
        outputFile.close();
        cout << "Your file has been converted to HTML! Please check your directory." << endl;

    }catch (fileException& ex){
        cout << ex.what() << endl;
    }
    catch(...){
        cout << "An unknown error occurred." << endl;
    }
    return 0;
}

void validate(string fileName){

/*    if (regex_match(fileName,regex("CON|PRN|AUX|NUL|COM1|COM2|COM3|COM4|COM5|COM6|COM7"
                                   "|COM8|COM9|LPT1|LPT2|LPT3|LPT4|LPT5|LPT6|LPT7|LPT8|LPT9"))){
        throw invalid_argument("This file name is being used by the system. Please choose another name.");
    }else*/
    if(!regex_match(fileName,regex(R"([a-zA-Z]\:[a-zA-Z0-9\s?_\\]*)"))){//Regex matches drive letter, and full directory path. user must not enter file type
        throw invalid_argument("Error in file path.\n Please make sure you have a drive letter, all characters are valid, and there is no file type.\n (e.g. C:\\files\\inFile)");
    }
}