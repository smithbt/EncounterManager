#pragma once

#include <QAbstractTableModel>
#include <QVector>

struct Combatant {
	QString name;
	int initBonus;
	int maxHP;
	bool isPlayer;
	QString player;
	bool operator==(const Combatant& other) const
	{
		return name == other.name 
			&& initBonus == other.initBonus
			&& maxHP == other.maxHP
			&& isPlayer == other.isPlayer
			&& player == other.player;
	}
};

inline QDataStream& operator<<(QDataStream& stream, const Combatant& cmbtnt)
{
	return stream 
		<< cmbtnt.name 
		<< QString(cmbtnt.initBonus) 
		<< QString(cmbtnt.maxHP)
		<< QString(cmbtnt.isPlayer)
		<< cmbtnt.player;
}

inline QDataStream& operator>>(QDataStream& stream, Combatant& cmbtnt)
{
	return stream
		>> cmbtnt.name
		>> QString(cmbtnt.initBonus)
		>> QString(cmbtnt.maxHP)
		>> QString(cmbtnt.isPlayer)
		>> cmbtnt.player;
}

class CombatantModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	CombatantModel(QObject *parent = nullptr);
	~CombatantModel(); 

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	bool setData(const QModelIndex& index, const QVariant &val, int role = Qt::EditRole) override;
	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
	bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

private:
	QVector<Combatant> combatants;
};
