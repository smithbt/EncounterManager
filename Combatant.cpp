#include "Combatant.h"

Combatant::Combatant()
{
}

Combatant::Combatant(QString name, bool pc)
{
	this->name = name;
	this->isPlayer = pc;
}

Combatant::~Combatant()
{
}

void Combatant::setName(QString name)
{
	this->name = name;
}

void Combatant::setIsPlayer(bool isPlayer)
{
	this->isPlayer = isPlayer;
}

void Combatant::setPlayer(QString player)
{
	this->player = player;
}

void Combatant::setInitBonus(int initBonus)
{
	this->initBonus = initBonus;
}

void Combatant::setMaxHP(int maxHP)
{
	this->maxHP = maxHP;
}

void Combatant::setOtherInfo(QString otherInfo)
{
	this->otherInfo = otherInfo;
}

QString Combatant::getName()
{
	return name;
}

bool Combatant::isPC()
{
	return isPlayer;
}

QString Combatant::getPlayer()
{
	return player;
}

int Combatant::getInitBonus()
{
	return initBonus;
}

int Combatant::getMaxHP()
{
	return maxHP;
}

QString Combatant::getOtherInfo()
{
	return otherInfo;
}
