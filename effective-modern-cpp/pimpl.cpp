#include<string>
#include<iostream>
#include<vector>

#include "pimpl.h"

Pimpl::Pimpl(){}

struct Pimpl::pimpl{
	std::string here;
	std::vector<std::string> str_vec;
};


void Pimpl::out_str(){
	std::cout<<P_im->here;
}
Pimpl::Pimpl(Pimpl&& rhs)=default;

Pimpl& Pimpl::operator =(Pimpl &&rhs)=default;

Pimpl::Pimpl(Pimpl& rhs){
	this->P_im=std::make_unique<pimpl>(*(rhs.P_im));
}

Pimpl& Pimpl::operator =(const Pimpl &rhs){
	this->P_im=std::make_unique<pimpl>(*(rhs.P_im));
	return *this;
}

Pimpl::~Pimpl(){}
