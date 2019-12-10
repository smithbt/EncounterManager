#pragma once

#include <QString>

class Combatant
{
private:
	QString name;
	bool isPlayer;
	QString player;
	int initBonus;
	int maxHP;
	QString otherInfo;

public:
	Combatant();
	Combatant(QString name, bool pc);
	~Combatant();

	void setName(QString name);
	void setIsPlayer(bool isPlayer);
	void setPlayer(QString player);
	void setInitBonus(int initBonus);
	void setMaxHP(int maxHP);
	void setOtherInfo(QString otherInfo);

	QString getName();
	bool isPC();
	QString getPlayer();
	int getInitBonus();
	int getMaxHP();
	QString getOtherInfo();
	bool isEmpty();
};

