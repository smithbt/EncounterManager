#pragma once

#include <QAbstractTableModel>
#include <QVector>

struct Combatant {
	QString name;
	int initBonus;
	int initRoll;
	int maxHP;
	bool isPlayer;
	QString player;
	bool operator==(const Combatant& other) const
	{
		return name == other.name 
			&& initBonus == other.initBonus
			&& initRoll == other.initRoll
			&& maxHP == other.maxHP
			&& isPlayer == other.isPlayer
			&& player == other.player;
	}
	Combatant() {
		name = QString();
		initBonus = 0;
		initRoll = 0;
		maxHP = 0;
		isPlayer = false;
		player = QString();
	}
};

inline QDataStream& operator<<(QDataStream& stream, const Combatant& cmbtnt)
{
	return stream 
		<< cmbtnt.name 
		<< QString(cmbtnt.initBonus) 
		<< QString(cmbtnt.initRoll)
		<< QString(cmbtnt.maxHP)
		<< QString(cmbtnt.isPlayer)
		<< cmbtnt.player;
}

inline QDataStream& operator>>(QDataStream& stream, Combatant& cmbtnt)
{
	return stream
		>> cmbtnt.name
		>> QString(cmbtnt.initBonus)
		>> QString(cmbtnt.initRoll)
		>> QString(cmbtnt.maxHP)
		>> QString(cmbtnt.isPlayer)
		>> cmbtnt.player;
}

class CombatantModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	enum CombatantField : int {
		NAME = 0,
		INITIATIVE_ROLL = 1,
		INITIATIVE_BONUS = 2,
		MAX_HP = 3,
		IS_PLAYER = 4,
		PLAYER_NAME = 5
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
