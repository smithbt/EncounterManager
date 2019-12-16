#pragma once

#include <QAbstractTableModel>
#include <QVector>
#include <QBrush>
#include "Combatant.h"

class CombatantModel : public QAbstractTableModel
{
	Q_OBJECT

public:
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
