#ifndef xml_h
#define xml_h

#include <string>
#include <cstddef>
#include "LinkedStack.h"

namespace structures {
class Xml {
 public: 
    Xml(std::string text);
    std::string valor(const std::string &inicio, const std::string &fim, std::size_t pos);
    std::size_t get_posicao();
    bool validacao();
    void set_posicao(std::size_t pos);
 private:
    //o xml em si
    std::string texto;
    //um pointer para definir qual posição do xml foi lida por ultimo
    std::size_t posicao;
};
  
} //namespace structures

#endif
//-----------------------------------------------

structures::Xml::Xml(std::string text) {
  texto = text;
}

//Pega o xml e retorna uma substring começando do indicide_incial
//até o indice_final, considerando a posição relativa que ja foi percorrida 
std::string structures::Xml::valor(const std::string &inicio, const std::string &fim, std::size_t posicao) {
    //função find procura o que esta no primeiro argumento a partir do indice do segundo argumento
    std::size_t indice_inicial = texto.find(inicio, posicao);
    std::size_t indice_final = texto.find(fim, indice_inicial);

    if (indice_inicial != -1 || indice_final != -1) {
        indice_inicial += inicio.length();
        std::size_t tamanho = indice_final - indice_inicial;
        //altera a posicao atual do 'pointer' do xml para não percorrer coisas repetidas
        set_posicao(indice_final + fim.length());
        //retorna a substring dentro da range definida
        return texto.substr(indice_inicial, tamanho);
    }
    //caso não haja mais texto para ser lido, define posição como -1 
    set_posicao(-1);
    return "";

}

//setter
void structures::Xml::set_posicao(std::size_t pos){
  posicao = pos;
}

//getter
std::size_t structures::Xml::get_posicao(){
  return posicao;
}

//função para validar o arquivo xml
//testa as aberturas e fechamentos das tags
bool structures::Xml::validacao() {
  std::size_t posicao = 0;
  std::size_t tamanho = texto.length();
  structures::LinkedStack<std::string> arquivo_xml;

  do {
    std::size_t inicio = texto.find("<", posicao);
    std::size_t fim = texto.find(">", inicio);
    //se não houver tag de abertura da break
    if (inicio == -1) { break;} 
    //se não houver uma tag de fechamento mas houver de abertura ja é inválido 
    else if (fim == -1) { return false;}
    
    std::string marcacao = texto.substr(inicio, (fim + 1) - (inicio));
    posicao = fim + 1;
    tamanho = texto.length();
    //caso não seja uma tag de fechamento insere a marcação para comparar depois
    if (marcacao[1] != '/') {
			arquivo_xml.push(marcacao.insert(1, "/"));
		//comparar o topo da pilha para ver se é igual a tag atual
		//como foi inserido o '/' caso esteja certo vão ser iguais
		} else if (arquivo_xml.top() == marcacao) {
            arquivo_xml.pop();
    } else {
        //caso seja uma tag de fechamento e o topo da pilha seja diferente
        //o arquivo esta com ordem de fechamento de tag erradas e é inválido
        return false;
      }
    
    } while (posicao < tamanho);
    return arquivo_xml.empty();
}