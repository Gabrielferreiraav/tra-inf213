#ifndef HSV_2_RBG_H
#define HSV_2_RBG_H

//Converte HSV para RGB (é mais fácil mapear uma escala linear para HSV do que para RGB)
//Assim, vamos maepar as distancias para o formato HSV e, a serguir, converter para RGB
//Codigo de hsv2rgb baseado em : https://stackoverflow.com/a/36209005
struct Cor {
    int r;
    int g;
    int b;

    Cor(int r, int g, int b) : r(r), g(g), b(b) {}
};

typedef struct {
    double h;       // ∈ [0, 360]
    double s;       // ∈ [0, 1]
    double v;       // ∈ [0, 1]
} hsv;

typedef struct {
    double r;       // ∈ [0, 1]
    double g;       // ∈ [0, 1]
    double b;       // ∈ [0, 1]
} rgb;

rgb hsv2rgb(hsv HSV);
Cor geraCorDist(double distPercent);

#endif // HSV_2_RBG