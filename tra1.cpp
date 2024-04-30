#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

//conferir funcionamento de get em ED
//criar git para o trabalho
//criar uma cronologia da elaboração do trabalho
/*1 - Criação da class MyMatrix para melhor eficiência e desempenho das consultas de dados
 que serão armazenadas durante as operações e consulta*/ 

template<typename T>
class MyMatrix {
private :
    int linhas;
    int colunas;
    T** valor;

public:
    MyMatrix(int linhas, int colunas) : linhas(linhas),colunas(colunas){
        valor = new T*[linhas];
        for(int i =0;i<linhas;i++){
            valor[i] = new T[colunas];
        }
    }

    ~MyMatrix(){
        for (init i =0;i<linhas;i++){
            delete[] valor[i];
        }
        delete[] valor;
    }

    T get(int i,int j) const{
        return valor[i][j];
    }

    void set(int i, int j, T objeto){
        valor[i][j] = objeto;
    }

};
//utlização do algoritmo de euclidiano para calcular a a distancia entre celulas
double calculoDistancia(int x1,int y1,int x2,int y2){
    return sqrt(pow(x2-x1,2)+ pow(y2-y1,2));
}
/*2 - Função de processemento da imagens recebidas*/
//Pode melhorara eficiência utilizando um map para associar cada caso
//incompleto pois é a parte central de processamento de dados
//revisar a logica dessa função
void processamento(const MyMatrix<int>&imagem, const string& algoritmo, const string& outputMode){
    if(algoritmo == "trivial"){

    }else if (algoritmo == "melhorado"){

    }else if(algoritmo == "eficiente"){

    }else{//caso que n existe o algoritmo

    }

    //Parte da saida
    if (outputMode == "distancia"){

    }else if(outputMode == "resumo"){

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
int main (int argc, char* arg[]){
    if(argc != 3){
        cerr << "Uso: " << argv[0] << " ALGORITMO MODO_SAIDA < entrada.ppm > saida.ppm" << std::endl;
        return 1;
    }

    string algoritmo = argv[1];
    string outputMode = argv[2];

    //Imagem PPM
    string formato;
    int largura,altura,maxCor;
    cin >> formato >> largura >> altura >> maxCor;

    MyMatrix<int> imagem(largura,altura);
    for (int i = 0; i < altura; ++i)
    {
        for(int j = 0; j<largura;++j){
            int r,g,b;
            cin >> r >> g >> b;
            int gray = (r+g+b)/3;
            imagem.set(i,j,gray);
        }
    }

    //NUCLEO DE PROCESSAMENTO NA MAIN
    processamento(imagem,algoritmo,outputMode);

    return 0;
    
}