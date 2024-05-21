#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Cor {
    int r, g, b;
    Cor(int r, int g, int b) : r(r), g(g), b(b) {}
};

typedef struct {
    double h;  // ∈ [0, 360]
    double s;  // ∈ [0, 1]
    double v;  // ∈ [0, 1]
} hsv;

hsv rgb2hsv(Cor RGB) {
    double r = RGB.r / 255.0;
    double g = RGB.g / 255.0;
    double b = RGB.b / 255.0;

    double maxVal = std::max({r, g, b});
    double minVal = std::min({r, g, b});
    double delta = maxVal - minVal;

    hsv out;
    out.v = maxVal;

    if (delta < 0.00001) {
        out.s = 0;
        out.h = 0;  // undefined, maybe nan?
        return out;
    }

    if (maxVal > 0.0) {
        out.s = delta / maxVal;  // s
    } else {
        // if max is 0, then r = g = b = 0
        out.s = 0.0;
        out.h = NAN;  // undefined
        return out;
    }

    if (r >= maxVal)
        out.h = (g - b) / delta;        // between yellow & magenta
    else if (g >= maxVal)
        out.h = 2.0 + (b - r) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + (r - g) / delta;  // between magenta & cyan

    out.h *= 60.0;  // degrees

    if (out.h < 0.0)
        out.h += 360.0;

    return out;
}

double getDistPercent(Cor RGB) {
    hsv hsvColor = rgb2hsv(RGB);
    return hsvColor.h / 360.0;
}

void printDistPercentMatrix(const vector<vector<Cor>>& rgbMatrix) {
    for (const auto& row : rgbMatrix) {
        for (const auto& color : row) {
            double distPercent = getDistPercent(color);
            cout << distPercent << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<Cor>> rgbMatrix = {
        {Cor(85, 255, 0), Cor(209, 255, 0), Cor(209, 255, 0), Cor(85, 255, 0), Cor(0, 255, 160), Cor(0, 71, 255)},
        {Cor(209, 255, 0), Cor(0, 0, 0), Cor(0, 0, 0), Cor(209, 255, 0), Cor(0, 255, 90), Cor(0, 119, 255)},
        {Cor(85, 255, 0), Cor(209, 255, 0), Cor(209, 255, 0), Cor(85, 255, 0), Cor(0, 255, 160), Cor(0, 71, 255)},
        {Cor(0, 255, 160), Cor(0, 255, 90), Cor(0, 255, 90), Cor(0, 255, 160), Cor(0, 171, 255), Cor(61, 0, 255)},
        {Cor(0, 71, 255), Cor(0, 119, 255), Cor(0, 119, 255), Cor(0, 71, 255), Cor(0, 71, 255), Cor(0, 119, 255)},
        {Cor(217, 0, 255), Cor(180, 0, 255), Cor(61, 0, 255), Cor(0, 171, 255), Cor(0, 255, 160), Cor(0, 255, 90)},
        {Cor(255, 0, 0), Cor(217, 0, 255), Cor(0, 71, 255), Cor(0, 255, 160), Cor(85, 255, 0), Cor(209, 255, 0)},
        {Cor(255, 0, 29), Cor(180, 0, 255), Cor(0, 119, 255), Cor(0, 255, 90), Cor(209, 255, 0), Cor(0, 0, 0)}
    };

    printDistPercentMatrix(rgbMatrix);

    return 0;
}
