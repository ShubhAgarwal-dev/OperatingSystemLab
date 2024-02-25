#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;
#define SLEEP_TIME 10

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
    // Finding height and width
    stringstream ss(currentLine);
    while (getline(ss, currValue, ' '))
        image->height == -1 ? image->height = stoi(currValue) : image->width = stoi(currValue);
    // Finding maximum color value
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

void fill_shared_memory(Image *image, int *red, int *green, int *blue)
{
    int n = image->colorSpace[0].size();
    for (int i = 0; i < n; i++)
    {
        red[i] = image->colorSpace[0][i];
        green[i] = image->colorSpace[1][i];
        blue[i] = image->colorSpace[2][i];
    }
    cout << "Fill working\n";
}

void dump_shared_memory(Image *image, int *red, int *green, int *blue)
{
    int n = image->colorSpace[0].size();
    for (int i = 0; i < n; i++)
    {
        image->colorSpace[0][i] = red[i];
        image->colorSpace[1][i] = green[i];
        image->colorSpace[2][i] = blue[i];
    }
    cout << "Dump working\n";
}

void toGrayscale(Image *image, int *red, int *green, int *blue)
{
    int n = image->width * image->height;
    for (int i = 0; i < n; i++)
    {
        double new_val = (double)red[i] * GRAYSCALE[0] + (double)green[i] * GRAYSCALE[1] + (double)blue[i] * GRAYSCALE[2];
        red[i] = blue[i] = green[i] = new_val;
    }
    cout << "Grayscale working\n";
}

void toInvert(Image *image, int *red, int *green, int *blue)
{
    int n = image->width * image->height;
    for (int i = 0; i < n; i++)
    {
        int R, G, B;
        R = red[i];
        G = green[i];
        B = blue[i];
        red[i] = 255 - (G + B) / 2;
        green[i] = 255 - (R + B) / 2;
        blue[i] = 255 - (G + R) / 2;
    }
    cout << "Invert working\n";
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
    key_t key_blue = ftok(argv[2], 'a');
    key_t key_green = ftok(argv[2], 'b');
    key_t key_red = ftok(argv[2], 'c');
    originalFile.open(argv[1]);
    outputFile.open(argv[2]);
    readFile(originalFile, &image);
    int numPixels = sizeof(int) * image.height * image.width;
    int shmid_blue = shmget(key_blue, numPixels, 0666 | IPC_CREAT);
    int shmid_red = shmget(key_red, numPixels, 0666 | IPC_CREAT);
    int shmid_green = shmget(key_green, numPixels, 0666 | IPC_CREAT);
    if (shmid_red == -1 || shmid_green == -1 || shmid_blue == -1)
    {
        cout << "SHMGET fault\n";
        return 1;
    }
    int *blue = (int *)shmat(shmid_blue, NULL, 0);
    int *green = (int *)shmat(shmid_green, NULL, 0);
    int *red = (int *)shmat(shmid_red, NULL, 0);
    fill_shared_memory(&image, red, green, blue);
    pid_t pid = fork();
    if (pid == 0)
    {
        toGrayscale(&image, red, green, blue);
        exit(0);
    }
    else
    {
        wait(NULL);
        toInvert(&image, red, green, blue);
    }
    dump_shared_memory(&image, red, green, blue);
    writeToFile(outputFile, &image);
    outputFile.close();
    originalFile.close();
    return 0;
}