#pragma once

#include <QAbstractTableModel>
#include <QVector>

struct Combatant {
	QString name;
	int initBonus;
	int initRoll;
	int curHP;
	int maxHP;
	bool isPlayer;
	QString player;
	QString otherInfo;
	bool operator==(const Combatant& other) const
	{
		return name == other.name 
			&& initBonus == other.initBonus
			&& initRoll == other.initRoll
			&& curHP == other.curHP
			&& maxHP == other.maxHP
			&& isPlayer == other.isPlayer
			&& player == other.player
			&& otherInfo == other.otherInfo;
	}
	Combatant() {
		name = QString();
		initBonus = 0;
		initRoll = 0;
		curHP = 0;
		maxHP = 0;
		isPlayer = false;
		player = QString();
		otherInfo = QString();
	}
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
		<< cmbtnt.otherInfo;
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
		>> cmbtnt.otherInfo;
}

class CombatantModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	enum CombatantField : int {
		NAME = 0,
		INITIATIVE_ROLL = 1,
		INITIATIVE_BONUS = 2,
		CUR_HP = 3,
		MAX_HP = 4,
		IS_PLAYER = 5,
		PLAYER_NAME = 6,
		OTHER_INFO = 7
	};
	CombatantModel(QObject *parent = nullptr);
	~CombatantModel(); 

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	bool setData(const QModelIndex& index, const QVariant &val, int role = Qt::EditRole) override;
	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
	bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
	Combatant getCombatantFromIndex(QModelIndex& index);
	const QVector<Combatant>& getAllCombatants() const;

private:
	QVector<Combatant> combatants;
};
