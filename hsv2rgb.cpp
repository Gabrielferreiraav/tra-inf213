//Converte HSV para RGB (é mais fácil mapear uma escala linear para HSV do que para RGB)
//Assim, vamos maepar as distancias para o formato HSV e, a serguir, converter para RGB
//Codigo de hsv2rgb baseado em : https://stackoverflow.com/a/36209005
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

rgb hsv2rgb(hsv HSV)
{
    rgb RGB;
    double H = HSV.h, S = HSV.s, V = HSV.v,
            P, Q, T,
            fract;

    (H == 360.)?(H = 0.):(H /= 60.);
    fract = H - floor(H);

    P = V*(1. - S);
    Q = V*(1. - S*fract);
    T = V*(1. - S*(1. - fract));

    if      (0. <= H && H < 1.)
        RGB = (rgb) { V, T, P};
    else if (1. <= H && H < 2.)
        RGB = (rgb){Q, V, P};
    else if (2. <= H && H < 3.)
        RGB = (rgb){P,  V,  T};
    else if (3. <= H && H < 4.)
        RGB = (rgb){P,  Q,  V};
    else if (4. <= H && H < 5.)
        RGB = (rgb){T,  P,  V};
    else if (5. <= H && H < 6.)
        RGB = (rgb){V,  P,  Q};
    else
        RGB = (rgb){0.,  0.,  0};

    return RGB;
}

//Dado um valor real entre 0 e 1, mapeia esse valor para uma cor...
//Ou seja, transforma uma escala linear em uma cor no formato r,g,b
TipoDeRetorno geraCorDist(double distPercent) {
	if(distPercent <= 0.00000001) {
		return Cor(0,0,0);
	}
	hsv corHSV;
	corHSV.h = 360*distPercent; //A entrada da funcao hsv2rgb usa valores de h entre 0 e 360 
	corHSV.s = 1;
	corHSV.v = 1;
	rgb c = hsv2rgb(corHSV);

    int rgbR = c.r*255; //Os componentes rgb gerados pela funcao hsv2rgb estao entre 0 e 1 --> precisamos converter para algo entre 0 e 255
    int rgbG = c.g*255;
    int rgbB = c.b*255;

    //rgbR,rgbG e rgbB sao os componentes RGB gerados. Adapte o resto do codigo para que ele retorne a cor utilizando o tipo que voce criou no seu trabalho...
	return .... //adapte ...
}
