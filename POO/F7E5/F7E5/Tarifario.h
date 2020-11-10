#pragma once
class Tarifario
{
	float precoMinuto;

public:
	Tarifario();
	virtual bool autorizaChamada();
	virtual bool autorizaPagamento();
	virtual float valoraPagar();
	virtual ~Tarifario();
};

