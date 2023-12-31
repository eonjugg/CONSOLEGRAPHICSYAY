/*
graph/plot data in the terminal
*/

#include <iostream>
#include <vector>
#include <__utility/pair.h>

using namespace std;

const int  dispX = 50;    // size of display
const int  dispY = 25;
const bool axes  = false; // display axises

double map(double val, double inMin, double inMax, double outMin, double outMax) {
    double mapped = ( ( (val - inMin) / (inMax - inMin) ) * (outMax - outMin) ) + outMin;
    return mapped; // return min(outMax, max(outMin, mapped));
}

/*
Prints a plot of dots contained in the 'points' vector to console.
Control the ranges of x and y that are displayed with minX, maxX, minY, maxY.
*/
void plot(vector< pair<double, double> > points, double minX, double maxX, double minY, double maxY) {
    
    bool pointsMatrix[dispX][dispY] = {false};

    // insert points into cell matrix...
    for (int i = 0; i < points.size(); i++) {
        pair<double,double> p = points[i];
        
        int xcell = map(p.first, minX, maxX, 0, dispX);
        int ycell = map(p.second, minY, maxY, 0, dispY);

        if ((xcell >= 0 && xcell < dispX) && (ycell >= 0 && ycell < dispY)) {
            pointsMatrix[xcell][ycell] = true;
        }
    }

    // find axes (axises?)
    int xzero = map(0, minX, maxX, 0, dispX);
    int yzero = map(0, minX, maxX, 0, dispY);

    // draw matrix...
    for (int y = dispY-1; y > -1; y--) {
        for (int x = 0; x < dispX; x++) {
            char c;

            // what symbol to draw (assuming it's in view range)
            if (x == xzero && y == yzero && axes) {
                c = '@'; // origin (0, 0)
            } else if (pointsMatrix[x][y]) {
                c = '*'; // point
            } else if (x == xzero && axes) {
                c = '|'; // y axis (all points x = 0)
            } else if (y == yzero && axes) {
                c = '-'; // x axis (all points y = 0)
            } else {
                c = ' '; // background
            }
            cout << c;
        }
        cout << endl;
    }

    printf("points: %i | range X:(%f, %f) Y:(%f, %f)", (int)points.size(), minX, maxX, minY, maxY);
    cout << endl;

}

void plot(vector< pair<double, double> > points) {

    // default range just fits all points
    double mnX, mxX, mnY, mxY = 0;

    for (pair<double, double> p : points) {
        if (p.first > mxX) mxX = p.first;
        if (p.first < mnX) mnX = p.first;
        if (p.second > mxY) mxY = p.second;
        if (p.second < mnY) mnY = p.second;  
    }

    plot(points, mnX, mxX, mnY, mxY);

}

int main(int argc, char * argv[]) {
    
    vector< pair<double,double> > ps;

    // generate points
    srand(time(0));
    for(int i = 0; i < 100; i++) {
        pair<double,double> nue;
        double lnr = 10.0 * rand() / RAND_MAX;
        nue.first = lnr + (lnr*lnr*0.3*rand()/RAND_MAX);
        nue.second = lnr + (lnr*lnr*0.3*rand()/RAND_MAX);
        ps.push_back(nue);
    }

    //plot(ps, -1, 10, -1, 10); 

    plot(ps);

}