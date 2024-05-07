#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

//criação do struct que ira armazenar as coordenadas do ponto preto
struct Ponto
{
    int linha;
    int coluna;

    Ponto(int linha, int coluna) : linha(linha), coluna(coluna){}
    Ponto():linha(0),coluna(0){}
};


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
    return sqrt(pow(x2-x1,2)+ pow(y2-y1,2));
}
/*2 - Função de processemento da imagens recebidas*/
//Pode melhorara eficiência utilizando um map para associar cada caso
//incompleto pois é a parte central de processamento de dados
//revisar a logica dessa função
void processamento(const MyMatrix<int>& imagem,const MyMatrix<int>& distancias, const string& algoritmo, const string& outputMode){
    if(algoritmo == "trivial"){
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
                                double distancia = round(calculoDistancia(i,j,linha,coluna));
                                if(distancia < minDistancia) minDistancia = distancia;
                            }
                            
                        }
                        
                    }
                   distancias.set(i,j,minDistancia);
                }
            }
            
        }
        
        
    }else if (algoritmo == "melhorado"){
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
                        double distancia = round(calculoDistancia(i,j,ponto.linha,ponto.coluna));
                        if(distancia < minDistancia) minDistancia = distancia;
                    }
                distancias.set(i,j,minDistancia);
                }
            }
        }

    }else if(algoritmo == "eficiente"){

    }else{//caso que n existe o algoritmo

    }

    //Parte da saida
    if (outputMode == "distancia"){
    int linhas = distancias.getLinhas();int colunas = distancias.getColuns();
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                cout << distancias.getValor(i,j) << " ";
            }
            cout << endl;
        }
    }else if(outputMode == "resumo"){
        int soma = 0;
        for (int i = 0; i < distancias.getLinhas(); i++)
        {
            for (int j = 0; j < distancias.getColuns(); j++)
            {
                soma += distancias.getValor(i,j);
            }   
        }
        cout << soma << endl;
        
    }else if(outputMode == "cor"){
        
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
    MyMatrix<int> distancias(linhas, colunas);
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
    processamento(imagem,distancias,algoritmo,outputMode);

    return 0;
    
}