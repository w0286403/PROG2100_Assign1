#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main() {
    string fileNameIn = "../files/inFile.cpp";
    string fileNameOut = "../files/outFile.html";
    string line;

    ifstream inputFile(fileNameIn);
    ofstream outputFile(fileNameOut,ios::app);

    while(!inputFile.eof()){
        getline(inputFile,line);
        cout << line << endl;
        outputFile << line << endl;
    }

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