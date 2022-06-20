#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include "problema1.h"
#include "problema2.h"
#include "LinkedQueue.h"

int main() {

    char xmlfilename[100];
    //declara as constantes de tags presentes nos xmls
    const std::string imgb= "<img>";
    const std::string imge= "</img>";
    const std::string nameb= "<name>";
    const std::string namee= "</name>";
    const std::string he= "</height>";
    const std::string hb= "<height>";
    const std::string wb= "<width>";
    const std::string we= "</width>";
    const std::string datab= "<data>";
    const std::string datae= "</data>";
    //seta dois size_t auxiliares
    std::size_t nada = 0;
    std::size_t pos = 0;
    //lê a entrada contendo o caminho relativo para os arquivos xml
    std::cin >> xmlfilename;  // entrada
    //tenta abrir o arquivo presente nesse caminho e cria duas strings auxiliares
    std::ifstream file(xmlfilename); std::string xmls; std::string linha;
    // vê se o arquivo abriu
    if (file.is_open()) {
        //se abriu, percorre as linhas e adiciona em xmls, uma string que conterá tudo oq 
        //o que se encontrava no xml
        do { xmls += linha; } while (getline(file, linha));
        //fecha o arquivo
        file.close();
    } else { std::cout << "error\n"; return -1;} //se deu erro, acaba a execução do programa

    //cria um item da classe Xml com valor da string lida no arquivo aberto
    structures::Xml outxml = structures::Xml(xmls);
    // verifica se todas as tags abrem e fecham, se não acaba a execução do programa
    if(!outxml.validacao() ){
        std::cout << "error\n";
        return -1;
    } else {
        //enquando pos (que inicia em 0) for menor que o comprimento da string (ou  número de posições dela)
        do {
            //pega a primeira imagem
            const std::string codigoimagem = outxml.valor(imgb, imge, pos);
            //soma a posição para o primeiro item depois de </img>
            pos = outxml.get_posicao();
            //se não tiver posição, acaba o loop
            if (pos == -1) {break;}
            //pega o dado lido entre <img> e </img> e cria um novo xml para ele
            structures::Xml novaimagem = structures::Xml(codigoimagem);
            //busca os elementos da imagem
            std::string nome = novaimagem.valor(nameb, namee, nada);
            const int altura = std::stoi(novaimagem.valor(hb, he,  nada));
            const int largura = std::stoi(novaimagem.valor(wb, we,  nada));
            const std::string dados = novaimagem.valor(datab, datae,  nada);
            //se a altura e a largura não forem válidas, acaba o programa
            if (!(altura > 0 && largura > 0)) {
                std::cout << "error\n";return -1;
            } else {

                //cria uma matriz com a altura e largura da imagem lida
            structures::Matriz<int> imagem = structures::Matriz<int>(altura, largura);
            //seta toda a matriz com os valores binários presentes entre <dado> </dado>
            imagem.set_toda_matriz(dados);
            // como querermos trabalhar com dados presentes em uma matriz, criamos um par pixel
            using pixel = std::pair<int, int>; structures::LinkedQueue<pixel> fila;
            // cria a matriz R com o mesmo tamanho da matriz acima
            structures::Matriz<int> R = structures::Matriz<int>(imagem.get_linha(), imagem.get_coluna());
            //cria o rótulo que começa com 1
            int rotulo = 1;
            //para toda a linha e toda coluna da matriz
            for (int l = 0; l < imagem.get_linha(); l++) {
                for (int c = 0; c < imagem.get_coluna(); c++) {
                    // se a matriz R está com 0 e a matriz imagem com 1, na posição l, c
                    if (!R.get_item_pos(l, c) && imagem.get_item_pos(l, c)) {
                        //seta o valor de R na posição para o valor do rótulo
                        R.set_item_pos(l, c, rotulo);
                        //coloca essa tupla em uma fila
                        fila.enqueue({l, c});
                        //enquanto a fila não estiver vazia
                        while (!fila.empty()) {
                            //tira da fila o item mais antigo
                            const pixel p = fila.dequeue();
                            int x = p.first;
                            int y = p.second;
                            //busca a vizinhança 4, verifica se o item nessa posição é 1 e se sim
                            //coloca na fila
                            if (x - 1 >= 0 && !R.get_item_pos(x-1, y)) {
                                if (imagem.get_item_pos(x-1,y)){
                                    R.set_item_pos(x-1, y, rotulo);
                                    fila.enqueue({x-1, y});
                                }
                            }
                            
                            if (x + 1 < imagem.get_linha()) {
                                if (!R.get_item_pos(x+1, y) ){
                                    if(imagem.get_item_pos(x+1, y)){  
                                        R.set_item_pos(x+1, y, rotulo);
                                        fila.enqueue({x+1, y});
                                    }
                                }
                            }
                            
                            if (y - 1 >= 0 && !R.get_item_pos(x, y-1)) {
                                if (imagem.get_item_pos(x, y-1)){
                                    R.set_item_pos(x, y-1, rotulo);
                                    fila.enqueue({x, y-1});
                                }
                                
                            }
                            
                            if (y + 1 < imagem.get_coluna()) {
                                if (!R.get_item_pos(x, y+1) ){
                                    if (imagem.get_item_pos(x, y+1)){
                                        R.set_item_pos(x, y+1, rotulo);
                                        fila.enqueue({x, y+1});
                                    }
                                }
                                
                            }
                        }
                        //incrementa o rótulo
                        rotulo++;
                    }
                }
            }
            //o valor do maior caminho - 1 (pois o rótulo começa em 1) é printado junto com o nome da imagem
            std::cout << nome << " " << rotulo-1 << "\n";  
            }
        } while (pos < xmls.length());
        
    }

    

    return 0;
}