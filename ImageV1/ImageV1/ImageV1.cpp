// ImageV1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<int>dot;
ofstream toolPat;

int width;
bool checkNear(vector<vector<int>>& outL, int i, int j);
int getx(int i);
int gety(int i);


int main()
{
    ofstream image;
    image.open("image.pbm");
    ofstream finVect;
    finVect.open("vect.txt");
    ofstream outLine;
    outLine.open("outLine.pbm");

    toolPat.open("toolPat.txt");
    ifstream source;
    source.open("for.ppm");

    string type, max;
    int height;
    source >> type >> width >> height >> max;
    image << "P3" << endl << width << " " << height << endl;

    vector<vector<int>> outL(width, vector<int>(height, 0));
    int r, g, b;
    int threshold = 125;

    int j = 1;
    cout << width << " " << height << endl;
    cout << "started" << endl;
    while (!source.eof()) {

        source >> r >> g >> b;

        if (r < threshold && g < threshold && b < threshold) {
            image << "1" << endl;
            dot.push_back(j);
        }
        else
        {
            image << "0" << endl;
        }
        j++;
    }
    cout << "pbm done" << endl << "vect size: " << dot.size() << endl;

    for (int i = 0; i < dot.size(); i++) {
        finVect << dot.at(i) << ',';
    }
    cout << "vect exported" << endl;

    image.close();

    for (int i = 1; i < dot.size(); i++) {
        if (dot[i] != dot[i - 1] + 1) {
            outL[getx(i) - 1][gety(i) - 1] = 1;
        }
    }
    cout << "x+ done" << endl;

    for (int i = dot.size() - 2; i >= 0; i--) {
        if (dot[i] != dot[i + 1] - 1) {
            outL[getx(i) - 1][gety(i) - 1] = 1;
        }
    }
    cout << "x- done" << endl;

    int k = 1;
    bool check = 0;

    for (int i = 0; i < dot.size(); i++) {
        check = 0;
        for (k = 1; k < width; k++) {//(getx(i)-width) <= getx(i-k)
            if (i + k < dot.size() && getx(i) == getx(i + k)) {
                check = 1;
            }
        }

        if (check == 0) {
            outL[getx(i) - 1][gety(i) - 1] = 1;
        }
    }
    cout << "y+ done" << endl;

    for (int i = dot.size() - 1; i >= 0; i--) {
        check = 0;
        for (k = 1; k < width; k++) {//(getx(i)-width) <= getx(i-k)
            if (k < i && getx(i) == getx(i - k)) {
                check = 1;
            }
        }

        if (check == 0) {
            outL[getx(i) - 1][gety(i) - 1] = 1;
        }
    }
    cout << "y- done" << endl;

    outLine << "P1" << endl << width << " " << height << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            outLine << outL[j][i];
        }
        outLine << endl;
    }
    cout << "toolPat finished" << endl;



    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            checkNear(outL, i, j);

            //toolPat << outL[i][j] << endl;
        }

    }

    return 0;
}

bool checkNear(vector<vector<int>>& outL, int i, int j) {
    if (outL[i][j] == 1) {
        toolPat << i << "," << j << ",";
        outL[i][j] = 0;
        if (outL[i + 1][j] == 1) {
            checkNear(outL, ++i, j);
        }
        if (outL[i + 1][j - 1] == 1) {
            checkNear(outL, ++i, --j);
        }
        if (outL[i][j - 1] == 1) {
            checkNear(outL, i, --j);
        }
        if (outL[i - 1][j - 1] == 1) {
            checkNear(outL, --i, --j);
        }
        if (outL[i - 1][j] == 1) {
            checkNear(outL, --i, j);
        }
        if (outL[i - 1][j + 1] == 1) {
            checkNear(outL, --i, ++j);
        }
        if (outL[i][j + 1] == 1) {
            checkNear(outL, i, ++j);
        }
        if (outL[i + 1][j + 1] == 1) {
            checkNear(outL, ++i, ++j);
        }
        //toolPat << -1 << ",";
    }
    else {
        return 0;

    }
}


int getx(int i) {
    return (dot[i] % width);
}

int gety(int i) {
    return (dot[i] / width);
}