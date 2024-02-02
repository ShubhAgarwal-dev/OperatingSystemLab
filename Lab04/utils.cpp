#include "utils.h"
#include <bits/stdc++.h>

using namespace std;

void read_file(const string &filename){
    ifstream myfile(filename);

    if (!myfile) {
        printf("File doesn't exist");
        exit(-1);
    }

    istream_iterator<string> fileIterator(myfile);
    istream_iterator<string> endIterator;

    while(fileIterator != endIterator){
        string word = *fileIterator;
        if (strcmp(word, "<")) {
            ++fileIterator;
        }
        ++fileIterator;
    }

    myfile.close();
}