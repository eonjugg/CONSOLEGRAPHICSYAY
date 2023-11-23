#include <iostream>
#include <fstream>

using namespace std;

class Complex {
    double real;
    double imag;

    public:

    Complex(double r, double i) {
        real = r;
        imag = i;
    }

    void square() {
        //   (a + bi) * (a + bi)
        // = aa + abi + abi + bibi
        // = aa + 2abi - bb
        // = (a^2 - b^2) + (2ab)i
        
        double realT, imagT;
        realT = real*real - imag*imag;
        imagT = 2*real*imag;

        real = realT;
        imag = imagT;
    }

    void mult() {
        //   (a + bi) * (c + di)
        // = ac + adi + cbi + bidi <- bidi=bd(i*i)=-bd
        // = ac + (ad + cb)i - bd
        // = (ac - bd) + (ad + cb)i
    }

    double dist() {
        return sqrt(imag*imag + real*real);
    }

    friend Complex operator+(Complex a, Complex b) {
        return Complex(a.real + b.real, a.imag + b.imag);
    }

    friend ostream& operator<<(ostream& out, const Complex& op) {
        out << op.real;
        out << (op.imag >= 0 ? " + " : " - ");
        out << abs(op.imag) << "i";
        return out;
    }

};

bool in_set(Complex c, int iterations) {
    bool decided = false;
    Complex total(0, 0);
    for (int i = 0; i < 10; i++) {
        total.square();
        total = total + c;
        if (total.dist() > 2) {
            decided = true;
            break;
        }
    }
    return !decided;
}

int main(int argc, char * argv[]) {
    
    const double cX = -0.6;     // coordinate at center of display
    const double cY = 0;     
    const double zoom = 2.5;   // how many units across is the display
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

            Complex check(xMap, yMap);
            if (in_set(check, dietinf)) {
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