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

bool Combatant::operator!=(const Combatant& other) const
{
	return !(*this == other);
}

void Combatant::read(const QJsonObject& json)
{
	if (json.contains("name") && json["name"].isString())
		name = json["name"].toString();
	if (json.contains("initBonus") && json["initBonus"].isDouble())
		initBonus = json["initBonus"].toInt();
	if (json.contains("initRoll") && json["initRoll"].isDouble())
		initRoll = json["initRoll"].toInt();
	if (json.contains("curHP") && json["curHP"].isDouble())
		curHP = json["curHP"].toInt();
	if (json.contains("maxHP") && json["maxHP"].isDouble())
		maxHP = json["maxHP"].toInt();
	if (json.contains("isPlayer") && json["isPlayer"].isBool())
		isPlayer = json["isPlayer"].toBool();
	if (json.contains("player") && json["player"].isString())
		player = json["player"].toString();
	if (json.contains("otherInfo") && json["otherInfo"].isString())
		otherInfo = json["otherInfo"].toString();
	if (json.contains("isCurrentTurn") && json["isCurrentTurn"].isBool())
		isCurrentTurn = json["isCurrentTurn"].toBool();
}

void Combatant::write(QJsonObject& json) const
{
	json["name"] = name;
	json["initBonus"] = initBonus;
	json["initRoll"] = initRoll;
	json["curHP"] = curHP;
	json["maxHP"] = maxHP;
	json["isPlayer"] = isPlayer;
	json["player"] = player;
	json["otherInfo"] = otherInfo;
	json["isCurrentTurn"] = isCurrentTurn;
}

QVariant Combatant::valueFromField(int field)
{
	switch (field) {
	case NAME: return name;
	case INITIATIVE_BONUS: return initBonus;
	case INITIATIVE_ROLL: return initRoll;
	case CUR_HP: return curHP;
	case MAX_HP: return maxHP;
	case IS_PLAYER: return isPlayer;
	case PLAYER_NAME: return player;
	case OTHER_INFO: return otherInfo;
	case CURRENT_TURN: return isCurrentTurn;
	default: return QVariant();
	}
	return QVariant();
}

bool Combatant::isEmpty()
{
	return (*this == Combatant());
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