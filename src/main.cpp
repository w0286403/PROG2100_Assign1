#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main() {
    string fileNameIn = "../files/inFile.cpp";
    string fileNameOut = "../files/outFile.html";
    string line;
    int index = 0;
    string bufferString;

    string lessThanString = "&lt;";
    string greaterThanString = "&gt;";

    ifstream inputFile(fileNameIn);
    ofstream outputFile(fileNameOut,ios::out);

    outputFile << "<PRE>" << endl;

    while(!inputFile.eof()){
        getline(inputFile,line);
        cout << line << endl;


        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == '<'){
                bufferString += lessThanString;
            }else if (line[i] == '>'){
                bufferString += greaterThanString;
            }else{
                bufferString += line[i];
            }
        }

        outputFile << bufferString << endl;
        bufferString.clear();
    }

    outputFile << "</PRE>" << endl;

    inputFile.close();
    outputFile.close();
    return 0;
}


/*
 * Read In cpp file line by line
 * Write each line to .html file
 * insert <PRE> as the first line
 * insert </PRE> as the last line
 *if < in line change it to &lt
 * if > in line change it to &gt
 */

/*        for (char i : line){

            if (i == '<'){
               *//* line.replace(index,1,"&lt;");
                index += (int)lessThanString.length()-1;*//*
            }
            if (i == '>'){
                *//*line.replace(index,1,"&gt;");
                index += (int)greaterThanString.length()-1;*//*
            }*/