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
    std::string texto;
    std::size_t posicao;
};
  
} //namespace structures

#endif
//-----------------------------------------------

structures::Xml::Xml(std::string text) {
  texto = text;
}

std::string structures::Xml::valor(const std::string &inicio, const std::string &fim, std::size_t posicao) {
    std::size_t indice_inicial = texto.find(inicio, posicao);
    std::size_t indice_final = texto.find(fim, indice_inicial);
    
    if (indice_inicial != -1 || indice_final != -1) {
        set_posicao(indice_final + fim.length());
        indice_inicial += inicio.length();
        std::size_t tamanho = indice_final - indice_inicial;
        return texto.substr(indice_inicial, tamanho);
    }
    set_posicao(-1);
    return "";

}

void structures::Xml::set_posicao(std::size_t pos){
  posicao = pos;
}

std::size_t structures::Xml::get_posicao(){
  return posicao;
}

bool structures::Xml::validacao() {
  std::size_t posicao = 0;
  std::size_t tamanho = texto.length();
  structures::LinkedStack<std::string> arquivo_xml;

  do {
    std::size_t inicio = texto.find("<", posicao);
    std::size_t fim = texto.find(">", inicio);
    
    if (inicio == -1) { break;} 
    else if (fim == -1) { return false;}
    
    std::string marcacao = texto.substr(inicio, (fim + 1) - (inicio));
    posicao = fim + 1;
    tamanho = texto.length();
    if (marcacao[1] != '/') {
			arquivo_xml.push(marcacao.insert(1, "/"));
		} else if (arquivo_xml.top() == marcacao) {
            arquivo_xml.pop();
    } else {
        return false;
      }
    
    } while (posicao < tamanho);
    return arquivo_xml.empty();
}