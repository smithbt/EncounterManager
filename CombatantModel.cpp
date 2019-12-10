#include "CombatantModel.h"

CombatantModel::CombatantModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

CombatantModel::~CombatantModel()
{
}

int CombatantModel::rowCount(const QModelIndex& parent) const
{
	return parent.isValid() ? 0 : combatants.count();
}

int CombatantModel::columnCount(const QModelIndex& parent) const
{
	return parent.isValid() ? 0 : 5; //Only 5 columns: name, init, hp, isPlayer, playerName
}

QVariant CombatantModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= combatants.size() || index.row() < 0)
		return QVariant();

	if (role == Qt::DisplayRole)
	{
		const auto &cbt = combatants.at(index.row());
		switch (index.column()) {
		case 0: return cbt.name;
		case 1: return cbt.initBonus;
		case 2: return cbt.maxHP; 
		case 3: return cbt.isPlayer;
		case 4: return cbt.player;
		default: break;
		}
	}
	return QVariant();
}

bool CombatantModel::setData(const QModelIndex& index, const QVariant &val, int role)
{
	if (index.isValid() && role == Qt::EditRole) {
		const int row = index.row();
		auto cmbtnt = combatants.at(row);

		switch (index.column()) {
		case 0:
			cmbtnt.name = val.toString();
			break;
		case 1:
			cmbtnt.initBonus = val.toInt();
			break;
		case 2:
			cmbtnt.maxHP = val.toInt();
			break;
		case 3: 
			cmbtnt.isPlayer = val.toBool();
			break;
		case 4: 
			cmbtnt.player = val.toString();
			break;
		default:
			return false;
		}

		combatants.replace(row, cmbtnt);
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });
		return true;
	}
	return false;
}

Qt::ItemFlags CombatantModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CombatantModel::insertRows(int row, int count, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginInsertRows(QModelIndex(), row, row + count - 1);

	for (int position = 0; position < count; ++position) {
		combatants.insert(row, { QString(), 0, 0, false, QString() });
	}

	endInsertRows();
	return true;
}

bool CombatantModel::removeRows(int row, int count, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginRemoveRows(QModelIndex(), row, row + count - 1);

	for (int position = 0; position < count; ++position) {
		combatants.removeAt(row);
	}

	endRemoveRows();
	return true;
}
