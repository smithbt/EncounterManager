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

QVariant Combatant::getFieldValue(int field) const
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

bool Combatant::setFieldValue(int field, const QVariant& value)
{
	switch (field) {
	case NAME: name = value.toString(); break;
	case INITIATIVE_ROLL: initRoll = value.toInt(); break;
	case CUR_HP: curHP = value.toInt(); break;
	case MAX_HP: maxHP = value.toInt(); break;
	case IS_PLAYER: isPlayer = value.toBool(); break;
	case PLAYER_NAME: player = value.toString(); break;
	case INITIATIVE_BONUS: initBonus = value.toInt(); break;
	case OTHER_INFO: otherInfo = value.toString(); break;
	case CURRENT_TURN: isCurrentTurn = value.toBool(); break;
	default: return false;
	}
	return true;
}

bool Combatant::isEmpty()
{
	return (*this == Combatant());
}