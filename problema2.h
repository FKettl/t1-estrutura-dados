#ifndef MATRIZ_QUESTAO2
#define MATRIZ_QUESTAO2

#include <cstdint>
#include <stdexcept>

namespace structures{

template<typename T>
class Matriz {
 public:

    Matriz(int linhas, int colunas);
    void set_toda_matriz(const std::string& dados);
	T get_item_pos(int linha, int coluna);
	void set_item_pos(int linha, int coluna, T dado );
    int get_linha();
    int get_coluna();
    ~Matriz();

 private:
    int linhas_;
    int colunas_;
    T** conteudos;
};

}  // namespace structures

#endif  // MATRIZ_QUESTAO2

template<typename T>
structures::Matriz<T>::Matriz(int linhas, int colunas) {
    linhas_ = linhas; colunas_ = colunas;
    conteudos = new T*[linhas_];
    for (int l = 0; l < linhas_; l++) {
        conteudos[l] = new T[colunas_];
        for (int c = 0; c < colunas_; c++) {
            conteudos[l][c] = 0;
        }
    }
}

template<typename T>
void structures::Matriz<T>::set_toda_matriz(const std::string& dados){

    int l = 0;
    int c = 0;
    for (auto inicio = dados.begin(); inicio != dados.end(); ++inicio) {
        const auto& ponto= *inicio;
        set_item_pos(l, c, int(ponto - '0'));
        c++; 
        if (c >= colunas_) {c = 0;l++;}
        if (l >= linhas_ && c >= colunas_ ) {break;}
                
    }
}

template<typename T>
T structures::Matriz<T>::get_item_pos(int linha, int coluna) {
    if (linha > linhas_ || coluna > colunas_) {
        throw std::out_of_range("Posição inválida");
    }
    return conteudos[linha][coluna];
}

template<typename T>
void structures::Matriz<T>::set_item_pos(int linha, int coluna, T dado) {
    if (linha > linhas_ || coluna > colunas_) {
        throw std::out_of_range("Posição inválida");
    }
    conteudos[linha][coluna] = dado;
}

template<typename T>
int structures::Matriz<T>::get_linha(){
    return linhas_;
}

template<typename T>
int structures::Matriz<T>::get_coluna(){
    return colunas_;
}

template<typename T>
structures::Matriz<T>::~Matriz() {
    for (int l = 0; l < linhas_; l++) {
        delete [] conteudos[l];
    }
    delete [] conteudos;
}
