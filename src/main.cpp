#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;
void validate(string);

struct fileException : public exception{
public:
    const string what(){
        return "File failed to open. Does it Exist and is it a cpp file?";
    }
};

int main() {
    string fileNameIn = "inFile";
    string fileNameOut = "outFile";
    ifstream inputFile;
    ofstream outputFile;
    string line;
    string bufferString;
    string lessThanString = "&lt;";
    string greaterThanString = "&gt;";
    bool willContinue = true;

    cout << "Please place your file inside the \"files\" directory." << endl;

    do {
        try {
            cout << "Enter the file name you would like to convert to html (e.g. \"inputFile\"):" << endl;
            getline(cin,fileNameIn);
            validate(fileNameIn);
            inputFile.open("../files/" + fileNameIn + ".cpp");
            if (inputFile.fail()){
                throw fileException();
            }

            cout << "Enter the file name for the output (e.g. \"outputFile\")" << endl;
            getline(cin,fileNameOut);
            validate(fileNameOut);
            outputFile.open("../files/" + fileNameOut + ".html",ios::out);
            if (outputFile.fail()){
                throw fileException();
            }
        }catch (fileException& ex){
            cout << ex.what() << endl;
            willContinue = false;
        }catch (const invalid_argument& e){
            cout << e.what() << endl;
            willContinue = false;
        }catch (...){
            willContinue = false;
        }
    }while(!willContinue);

    try{
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
    }catch(...){

    }
    cout << "Your file has been converted to HTML! Please check the \"files\" directory." << endl;
    return 0;
}

void validate(string fileName){

    if (regex_match(fileName,regex("CON|PRN|AUX|NUL|COM1|COM2|COM3|COM4|COM5|COM6|COM7"
                                   "|COM8|COM9|LPT1|LPT2|LPT3|LPT4|LPT5|LPT6|LPT7|LPT8|LPT9"))){
        throw invalid_argument("This file name is being used by the system.");
    }else if(!regex_match(fileName,regex("[a-zA-Z_]\\s?[a-zA-Z_0-9]*"))){
        throw invalid_argument("Received unacceptable file character.");
    }
    //[a-zA-Z_]\s?[a-zA-Z_0-9]*.[a-zA-Z0-9]+ REGEX FOR FILE TYPES
}