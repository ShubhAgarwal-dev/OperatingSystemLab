#include <bits/stdc++.h>
#include <semaphore.h>
#include <thread>

using namespace std;
mutex m1;

double GRAYSCALE[3] = {0.299, 0.587, 0.114};

class Image
{
public:
    string ppmVersion;
    int height = -1, width = -1, maxColorValue = -1, valsInLine = -1;
    vector<vector<int>> colorSpace = {{/*RED*/},
                                      {/*GREEN*/},
                                      {/*BLUE*/}};
    void printColorSpace()
    {
        for (int i = 0; i < 3; i++)
        {
            string s = (i == 0 ? "Red" : i == 1 ? "Green"
                                                : "Blue");
            cout << s << '\n';
            for (int x : this->colorSpace[i])
                cout << x << ',';
            cout << '\n';
        }
    }
};

void readFile(ifstream &originalFile, Image *image)
{
    string currentLine, currValue;
    int count = 0;
    getline(originalFile, image->ppmVersion);
    while (getline(originalFile, currentLine))
    {
        if (currentLine[0] == '#')
            continue;
        else
            break;
    }
    stringstream ss(currentLine);
    while (getline(ss, currValue, ' '))
        image->height == -1 ? image->height = stoi(currValue) : image->width = stoi(currValue);
    getline(originalFile, currentLine);
    image->maxColorValue = stoi(currentLine);

    while (getline(originalFile, currentLine))
    {
        stringstream currLineStringStream(currentLine);
        int valsInLine = 0;
        while (getline(currLineStringStream, currValue, ' '))
        {
            image->colorSpace[(count++) % 3].push_back(stoi(currValue));
            valsInLine++;
        }
        image->valsInLine = valsInLine;
    }
}

void toGrayscale(Image *image)
{
    m1.lock();
    int n = image->colorSpace[0].size();
    for (int i = 0; i < n; i++)
    {
        double newValue = 0.0;
        for (int j = 0; j < 3; j++)
            newValue += (double)image->colorSpace[j][i] * GRAYSCALE[j];
        for (int j = 0; j < 3; j++)
            image->colorSpace[j][i] = newValue;
    }
    m1.unlock();
}

void toInvert(Image *image)
{
    m1.lock();
    int n = image->colorSpace[0].size();
    for (int i = 0; i < n; i++)
    {
        int R, G, B;
        R = image->colorSpace[0][i];
        G = image->colorSpace[1][i];
        B = image->colorSpace[2][i];
        image->colorSpace[0][i] = 255 - (G + B) / 2;
        image->colorSpace[1][i] = 255 - (R + B) / 2;
        image->colorSpace[2][i] = 255 - (G + R) / 2;
    }
    m1.unlock();
}

void writeToFile(ofstream &outputFile, Image *image)
{
    outputFile << image->ppmVersion << '\n';
    outputFile << image->height << ' ' << image->width << '\n';
    outputFile << image->maxColorValue << '\n';
    int n = image->colorSpace[0].size();
    for (int i = 1; i < n + 1; i++)
    {
        outputFile << image->colorSpace[0][i - 1] << ' ';
        outputFile << image->colorSpace[1][i - 1] << ' ';
        outputFile << image->colorSpace[2][i - 1] << ' ';
        if ((i % (image->valsInLine / 3)) == 0)
            outputFile << '\n';
    }
    return;
}

int main(int argc, char const *argv[])
{
    Image image;
    ifstream originalFile;
    ofstream outputFile;
    originalFile.open(argv[1]);
    outputFile.open(argv[2]);
    readFile(originalFile, &image);
    // cout << "Read successful!!\n";
    thread t1(toGrayscale, &image);
    // toGrayscale(&image);
    thread t2(toInvert, &image);
    t1.join();
    t2.join();
    writeToFile(outputFile, &image);
    // cout << "Write successful!!\n";
    outputFile.close();
    originalFile.close();
}
