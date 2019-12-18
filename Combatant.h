#pragma once

#include <QString>
#include <QJsonObject>
#include <QVariant>

class Combatant
{
private:

public:
	Combatant();
	~Combatant();

	enum CombatantField : int {
		NAME = 0,
		INITIATIVE_ROLL = 1,
		INITIATIVE_BONUS = 2,
		CUR_HP = 3,
		MAX_HP = 4,
		IS_PLAYER = 5,
		PLAYER_NAME = 6,
		OTHER_INFO = 7,
		CURRENT_TURN = 8
	};

	QString name;
	int initBonus;
	int initRoll;
	int curHP;
	int maxHP;
	bool isPlayer;
	QString player;
	QString otherInfo;
	bool isCurrentTurn;

	bool operator==(const Combatant& other) const;
	bool operator!=(const Combatant& other) const;

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	QVariant valueFromField(int field);
	bool isEmpty();

	//void setName(QString name);
	//void setIsPlayer(bool isPlayer);
	//void setPlayer(QString player);
	//void setInitBonus(int initBonus);
	//void setMaxHP(int maxHP);
	//void setOtherInfo(QString otherInfo);
	
	//QString getName();
	//bool isPC();
	//QString getPlayer();
	//int getInitBonus();
	//int getMaxHP();
	//QString getOtherInfo();
	
};

inline QDataStream& operator<<(QDataStream& stream, const Combatant& cmbtnt)
{
	return stream
		<< cmbtnt.name
		<< QString(cmbtnt.initBonus)
		<< QString(cmbtnt.initRoll)
		<< QString(cmbtnt.curHP)
		<< QString(cmbtnt.maxHP)
		<< QString(cmbtnt.isPlayer)
		<< cmbtnt.player
		<< cmbtnt.otherInfo
		<< QString(cmbtnt.isCurrentTurn);
}

inline QDataStream& operator>>(QDataStream& stream, Combatant& cmbtnt)
{
	return stream
		>> cmbtnt.name
		>> QString(cmbtnt.initBonus)
		>> QString(cmbtnt.initRoll)
		>> QString(cmbtnt.curHP)
		>> QString(cmbtnt.maxHP)
		>> QString(cmbtnt.isPlayer)
		>> cmbtnt.player
		>> cmbtnt.otherInfo
		>> QString(cmbtnt.isCurrentTurn);
}