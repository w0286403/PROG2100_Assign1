#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <stdexcept>
using namespace std;
void validate(string);

struct fileException : public exception{
public:
    string message;
    fileException(string messageIn){
        this->message = messageIn;
    }
    const string what(){
        return "File failed to open. Does it Exist?" + message;
    }
};

int main() {
    string fileReg = "E:\\ITProgrammingFall2022\\PROG\\Assignment1\\files\\inFile.cpp";
    string fileNameIn = "inFile";
    string fileNameOut = "outFile";
    ifstream inputFile;
    ofstream outputFile;
    string line;
    string bufferString;
    string lessThanString = "&lt;";
    string greaterThanString = "&gt;";
    bool willContinue = true;

    cout << "\nFILE CONVERTER\n" << endl;
    cout << "Please make sure your file path includes a drive letter.\nDo not include the file type." << endl;

    do {
        try {
            cout << R"(Enter the path to the file you would like to convert to html. (e.g. C:\files\inputFile):)" << endl;
            getline(cin,fileNameIn);
            validate(fileNameIn);
            inputFile.open(fileNameIn + ".cpp");
            if (inputFile.fail()){
                throw fileException("asd");
            }

            cout << R"(Enter the path and name for the output html file. (e.g. C:\files\outputFile))" << endl;
            getline(cin,fileNameOut);
            validate(fileNameOut);
            outputFile.open(fileNameOut + ".html",ios::out);
            if (outputFile.fail()){
                throw fileException("aaaaaaaa");
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
    cout << "Your file has been converted to HTML! Please check your directory." << endl;
    return 0;
}

void validate(string fileName){

/*    if (regex_match(fileName,regex("CON|PRN|AUX|NUL|COM1|COM2|COM3|COM4|COM5|COM6|COM7"
                                   "|COM8|COM9|LPT1|LPT2|LPT3|LPT4|LPT5|LPT6|LPT7|LPT8|LPT9"))){
        throw invalid_argument("This file name is being used by the system. Please choose another name.");
    }else*/
    if(!regex_match(fileName,regex(R"([a-zA-Z]\:[a-zA-Z0-9\s?_\\]*)"))){
        throw invalid_argument("Error in file path.\n Please make sure you have a drive letter, all characters are valid, and there is no file type.\n (e.g. C:\\files\\inFile)");
    }
}