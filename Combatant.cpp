#include "Combatant.h"

Combatant::Combatant()
{
	name = QString();
	initBonus = 0;
	initRoll = 0;
	curHP = 0;
	maxHP = 0;
	isPlayer = false;
	player = QString();
	otherInfo = QString();
	isCurrentTurn = false;
}

Combatant::~Combatant()
{
}

bool Combatant::operator==(const Combatant& other) const
{
	return name == other.name
		&& initBonus == other.initBonus
		&& initRoll == other.initRoll
		&& curHP == other.curHP
		&& maxHP == other.maxHP
		&& isPlayer == other.isPlayer
		&& player == other.player
		&& otherInfo == other.otherInfo
		&& isCurrentTurn == other.isCurrentTurn;
}

//void Combatant::setName(QString name)
//{
//	this->name = name;
//}
//
//void Combatant::setIsPlayer(bool isPlayer)
//{
//	this->isPlayer = isPlayer;
//}
//
//void Combatant::setPlayer(QString player)
//{
//	this->player = player;
//}
//
//void Combatant::setInitBonus(int initBonus)
//{
//	this->initBonus = initBonus;
//}
//
//void Combatant::setMaxHP(int maxHP)
//{
//	this->maxHP = maxHP;
//}
//
//void Combatant::setOtherInfo(QString otherInfo)
//{
//	this->otherInfo = otherInfo;
//}
//
//QString Combatant::getName()
//{
//	return name;
//}
//
//bool Combatant::isPC()
//{
//	return isPlayer;
//}
//
//QString Combatant::getPlayer()
//{
//	return player;
//}
//
//int Combatant::getInitBonus()
//{
//	return initBonus;
//}
//
//int Combatant::getMaxHP()
//{
//	return maxHP;
//}
//
//QString Combatant::getOtherInfo()
//{
//	return otherInfo;
//}