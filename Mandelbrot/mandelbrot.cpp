/*

mandelbrot.cpp - prints characters to output file that draw the Mandelbrot Set at a specified zoom/location

args:

    1: display size
    2: iterations per point

*/

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char * argv[]) {

    const double cX = -0.6;  // x coordinate at center of display
    const double cY = 0;     // y
    const double zoom = 2.5; // how many units across is the display
    const int display = 100; // display size (square)
    const int dietinf = 50;  // number of iterations of z^2 + c to run to check for divergence

    const double pointdist = zoom/display;
    const double xoffset = cX - zoom/2.0;
    const double yoffset = cY - zoom/2.0;

    ofstream ofile("mandelbrot_out.txt");

    double xMap, yMap;

    for (int y = 0; y < display; y++) {
        for (int x = 0; x < display; x++) {

            xMap = xoffset + x*pointdist;
            yMap = yoffset + y*pointdist;

            double real = xMap;
            double imag = yMap;

            bool decided = false;
            for (int i = 0; i < dietinf; i++) {
                //   (a + bi) * (a + bi)
                // = aa + abi + abi + bibi
                // = aa + 2abi - bb
                // = (a^2 - b^2) + (2ab)i
                double tempX = real*real - imag*imag;
                double tempY = 2*real*imag;

                // + c
                real = tempX + xMap;
                imag = tempY + yMap;

                if (real*real + imag*imag > 4) { // sqrt(a^2 + c^2) > c  =>  a^2 + b^2 > c^2, c=2
                    decided = true;              // no sqrt = faster
                    break;
                }
            }

            if (!decided) {
                ofile << "##";
            } else {
                ofile << "..";
            }
        }
        ofile << endl;
    }

    ofile.close();

    cout << "Finished -> output.txt" << endl;

}