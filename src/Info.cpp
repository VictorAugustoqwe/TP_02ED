#include "Info.h"

//Construtor sem parâmetro.
Info::Info(){
    _nome = "";
    _dado = "";
}

//Construtor que inicia o dado e nome com o passado como parâmetro.
Info::Info(std::string nome, std::string dado){
    _nome = nome;
    _dado = dado;
}