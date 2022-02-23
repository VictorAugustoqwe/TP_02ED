#ifndef INFO_H
#define INFO_H

#include <iostream>

class Info{
    public:
        //Construtor sem parâmetro.
        Info();
        //Construtor que inicia o dado e nome com o passado como parâmetro.
        Info(std::string nome, std::string dado);
        //Nome da célula atual.
        std::string _nome;
        //Dado da célula atual.
        std::string _dado;
};

#endif