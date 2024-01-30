// ImageV1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ofstream image;
    image.open("image.ppm");

    ifstream source;
    source.open("JAKE.ppm");

    string type, width, height, max;
    source >> type >> width >> height >> max;
    image << type << endl << width << " " << height << endl << max << endl;
    //image << "P1" << endl << width << " " << height << endl;

    int r, g, b;



    while (!source.eof()) {

        source >> r >> g >> b;
        b += 50;
        if (b > 255) {
            b = 255;
        }
        image << r << endl << g << endl << b << endl;
    }


    /* if (image.is_open()) {
         image << "P3" << endl;
         image << "250 250" << endl;
         image << "255" << endl;
     }*/


     /*for (int y = 0; y < 250; y++) {
         for (int x = 0; x < 250; x++) {
             image << (x * y) % 255 << " " << x << " " << x << endl;
         }

     }*/


    image.close();
    return 0;


}



void filterBasic() {



}