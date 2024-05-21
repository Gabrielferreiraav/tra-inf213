#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;
/*5.1 - A biblioteca mencionada no item 5 */
#include "HSV_2_RBG_H.h"

//criação do struct que ira armazenar as coordenadas do ponto preto
struct Ponto
{
    int linha;
    int coluna;

    Ponto(int linha, int coluna) : linha(linha), coluna(coluna){}
    Ponto():linha(0),coluna(0){}
};

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
void geraCorDist(double distPercent) {
	if(distPercent <= 0.00000001) {
		cout << "0" << " " << "0"<< " " << "0" << " ";
        return;
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
	cout << rgbR << " " << rgbG << " " << rgbB << " ";
    return;//adapte ...
}

//conferir funcionamento de get em ED - feito
//criar git para o trabalho - feito
//criar uma cronologia da elaboração do trabalho
/*1 - Criação da class MyMatrix para melhor eficiência e desempenho das consultas de dados
 que serão armazenadas durante as operações e consulta*/ 
#include "MyMatrix.h"

/*4-Inclusão da bibliote MyVec para utilização do algoritmo trivial melhorado*/
#include "MyVec.h"


//utlização do algoritmo de euclidiano para calcular a a distancia entre celulas
double calculoDistancia(int x1,int y1,int x2,int y2){
    return sqrt(pow((x1-x2),2)+ pow((y1-y2),2));
}
void trivial (const MyMatrix<int>& imagem,const MyMatrix<double>& distancias){
    /*3- Criação do algoritmo trivial que faz o calulo das distancias de cada pixel branco ao pixel preto mais proximo*/
        int linhas = imagem.getLinhas(); int colunas = imagem.getColuns();
        //O(n²)
        //faz o calculo de distancias analisando todas as possibilidades
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if ((imagem.getValor(i,j)) == 255){
                    double minDistancia = calculoDistancia(0,0,linhas,colunas);
                    for (int linha = 0; linha < linhas; linha++)
                    {
                        for (int coluna = 0; coluna < colunas; coluna++)
                        {
                            if ((imagem.getValor(linha,coluna)) == 0)
                            {
                                double distancia = calculoDistancia(i,j,linha,coluna);
                                if(distancia < minDistancia) minDistancia = distancia;
                            }
                            
                        }
                        
                    }
                   distancias.set(i,j,minDistancia);
                }
            }
            
        }
}


void melhorado (const MyMatrix<int>& imagem,const MyMatrix<double>& distancias){
    /*5-Criação do algoritmo trivial melhorado, visando armazenar em Myvec os valores dos pontos pretos*/
        //utilização de ordenação indireta para armazenar ordenadamente os pixeis pretos
        int linhas = imagem.getLinhas(); int colunas = imagem.getColuns(); 
        MyVec<Ponto> pontosPreto;
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if (imagem.getValor(i,j) == 0)
                {
                    pontosPreto.push_back(Ponto(i,j));
                }
                
            }
            
        }
        //utilizando de modo parecido com algoritmo trivial
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if ((imagem.getValor(i,j)) == 255){
                    double minDistancia = calculoDistancia(0,0,linhas,colunas);
                    for (int pos = 0; pos < pontosPreto.size(); pos++)
                    {
                        const Ponto& ponto = pontosPreto[pos];
                        double distancia = calculoDistancia(i,j,ponto.linha,ponto.coluna);
                        if(distancia < minDistancia) minDistancia = distancia;
                    }
                distancias.set(i,j,minDistancia);
                
            }
        }
        }
}
/*2 - Função de processemento da imagens recebidas*/
//Pode melhorara eficiência utilizando um map para associar cada caso
//incompleto pois é a parte central de processamento de dados
//revisar a logica dessa função
void processamento(const MyMatrix<int>& imagem,const MyMatrix<double>& distancias, const string& outputMode){
    //if(algoritmo == "trivial"){
        /*3- Criação do algoritmo trivial que faz o calulo das distancias de cada pixel branco ao pixel preto mais proximo*/
        /*int linhas = imagem.getLinhas(); int colunas = imagem.getColuns();
        //O(n²)
        //faz o calculo de distancias analisando todas as possibilidades
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if ((imagem.getValor(i,j)) == 255){
                    double minDistancia = calculoDistancia(0,0,linhas,colunas);
                    for (int linha = 0; linha < linhas; linha++)
                    {
                        for (int coluna = 0; coluna < colunas; coluna++)
                        {
                            if ((imagem.getValor(linha,coluna)) == 0)
                            {
                                double distancia = calculoDistancia(i,j,linha,coluna);
                                if(distancia < minDistancia) minDistancia = distancia;
                            }
                            
                        }
                        
                    }
                   distancias.set(i,j,minDistancia);
                }
            }
            
        }*/
        
        
    //}else if (algoritmo == "melhorado"){
        
        /*5-Criação do algoritmo trivial melhorado, visando armazenar em Myvec os valores dos pontos pretos*/
        //utilização de ordenação indireta para armazenar ordenadamente os pixeis pretos
        /*int linhas = imagem.getLinhas(); int colunas = imagem.getColuns(); 
        MyVec<Ponto> pontosPreto;
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if (imagem.getValor(i,j) == 0)
                {
                    pontosPreto.push_back(Ponto(i,j));
                }
                
            }
            
        }
        //utilizando de modo parecido com algoritmo trivial
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if ((imagem.getValor(i,j)) == 255){
                    double minDistancia = calculoDistancia(0,0,linhas,colunas);
                    for (int pos = 0; pos < pontosPreto.size(); pos++)
                    {
                        const Ponto& ponto = pontosPreto[pos];
                        double distancia = calculoDistancia(i,j,ponto.linha,ponto.coluna);
                        if(distancia < minDistancia) minDistancia = distancia;
                    }
                distancias.set(i,j,minDistancia);
                
            }
        }
        }*/

    //}else if(algoritmo == "eficiente"){

    //}else{//caso que n existe o algoritmo

    //}

    //Parte da saida
    if (outputMode == "distancia"){
    int linhas = distancias.getLinhas();int colunas = distancias.getColuns();
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                cout << round(distancias.getValor(i,j)) << " ";
            }
            cout << endl;
        }
    }else if(outputMode == "resumo"){
        unsigned long long soma = 0;
        for (int i = 0; i < distancias.getLinhas(); i++)
        {
            for (int j = 0; j < distancias.getColuns(); j++)
            {
                soma += distancias.getValor(i,j);
            }   
        }
        cout << soma << endl;
        
    }else if(outputMode == "cor"){
        /*5- Criação do processamento de cor, utilizando uma biblioteca contendo structs conforme o programa ja disponibilizado e adptado*/
        int linhas = imagem.getLinhas(); int colunas = imagem.getColuns();
        double maxDistancia = 0;
        cout << "P3" << endl;
        cout << colunas << " " << linhas << endl;
        cout << "255" << endl;
        // Todo esse for é O(M*N)
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                double dist = distancias.getValor(i,j);
                if (dist > maxDistancia)
                {
                    maxDistancia = dist;
                }
                
            }
            
        }

        for (int i = 0; i < linhas; i++) //O(3*M*N) - > O(M*N)
        {
            for (int j = 0; j < colunas; j++)
            {
                double distPerct = distancias.getValor(i,j)/(maxDistancia);
                geraCorDist(distPerct);
            }
        cout << endl;
        }
        
        
    }else{//caso em que nao existe essa saida

    }
}

/*3- Criação da main para recebimento das informações da matriz

./programa.out ALGORITMO MODO_SAIDA < entrada.pbm > saida.pbm

P3
6 8
255
255 255 255    255 255 255    255 255 255    255 255 255    255 255 255    255 255 255
255 255 255    0 0 0                0 0 0                255 255 255    255 255 255    255 255 255
255 255 255    255 255 255    255 255 255    255 255 255    255 255 255    255 255 255
255 255 255    255 255 255    255 255 255    255 255 255    255 255 255    255 255 255
255 255 255    255 255 255    255 255 255    255 255 255    255 255 255    255 255 255
255 255 255    255 255 255    255 255 255    255 255 255    255 255 255    255 255 255
255 255 255    255 255 255    255 255 255    255 255 255    255 255 255    255 255 255
255 255 255    255 255 255    255 255 255    255 255 255    255 255 255    0 0 0

*/
int main (int argc, char* argv[]){
    if(argc != 3){
        cerr << "Uso: " << argv[0] << " ALGORITMO MODO_SAIDA < entrada.ppm > saida.ppm" << std::endl;
        return 1;
    }

    string algoritmo = argv[1];
    string outputMode = argv[2];

    //Imagem PPM
    string formato;
    int linhas,colunas,maxCor;
    cin >> formato >> colunas >> linhas >> maxCor;
    MyMatrix<double> distancias(linhas, colunas);
    MyMatrix<int> imagem(linhas,colunas);
    for (int i = 0; i < linhas; i++)
    {
        for(int j = 0; j<colunas;j++){
            int r,g,b;
            cin >> r >> g >> b;
            int gray = (r+g+b)/3;
            imagem.set(i,j,gray);
        }
    }

    //NUCLEO DE PROCESSAMENTO NA MAIN
    if (algoritmo == "trivial")
    {
        trivial(imagem,distancias);
    }else if (algoritmo == "melhorado")
    {
        melhorado(imagem,distancias);
    }
    processamento(imagem,distancias,outputMode);

    return 0;
    
}