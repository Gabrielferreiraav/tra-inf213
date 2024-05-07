#ifndef MYMATRIX_H
#define MYMATRIX_H

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
        for (int i =0;i<linhas;i++){
            delete[] valor[i];
        }
        delete[] valor;
    }

    T getValor(int i,int j) const{
        return valor[i][j];
    }

    T getLinhas() const{
        return linhas;
    }

    T getColuns() const{
        return colunas;
    }

    void set(int i, int j, T objeto) const{
        if (i < 0 || i >= linhas || j < 0 || j >= colunas) {
        // Se estiverem fora dos limites, exibe uma mensagem de erro e sai da função
        std::cerr << "Índices inválidos: (" << i << ", " << j << ")" << std::endl;
        return;
        }
        valor[i][j] = objeto;
    }

};

#endif //MYMATRIX_H