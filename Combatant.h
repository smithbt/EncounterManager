#pragma once

#include <QString>
#include <QJsonObject>
#include <QVariant>

class Combatant
{
private:
	QString name;
	int initBonus;
	int initRoll;
	int curHP;
	int maxHP;
	bool isPlayer;
	QString player;
	QString otherInfo;
	bool isCurrentTurn;

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

	bool operator==(const Combatant& other) const;
	bool operator!=(const Combatant& other) const;

	QVariant getFieldValue(int field) const;
	bool setFieldValue(int field, const QVariant& value);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	bool isEmpty();
	
};