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
	// Columns: name, initRoll, initBonus, curHP, maxHP, isPlayer, playerName, otherInfo, isCurrentTurn
	return parent.isValid() ? 0 : 9; 
}

QVariant CombatantModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	if (!index.isValid()) // invalid index
		return QVariant();

	if (row >= combatants.size() || row < 0) // out of range
		return QVariant();

	const Combatant& cbt = combatants.at(row); // relevant Combatant
	if (role == Qt::DisplayRole || role == Qt::EditRole)
		return cbt.getFieldValue(index.column());
	
	bool isCurTurn = cbt.getFieldValue(Combatant::CURRENT_TURN).toBool();
	if (role == Qt::BackgroundColorRole && isCurTurn)	{ 
		return QBrush(Qt::green);
	}
	return QVariant();
}

QVariant CombatantModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal) {
		switch (section) {
		case Combatant::NAME: return tr("Name");
		case Combatant::INITIATIVE_ROLL: return tr("Initiative Roll");
		case Combatant::INITIATIVE_BONUS: return tr("Initiative Bonus");
		case Combatant::CUR_HP: return tr("Current HP");
		case Combatant::MAX_HP: return tr("Max HP");
		case Combatant::IS_PLAYER: return tr("PC?");
		case Combatant::PLAYER_NAME: return tr("Player");
		case Combatant::OTHER_INFO: return tr("Other Info");
		case Combatant::CURRENT_TURN: return tr("Current Turn?");
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

		if (!cmbtnt.setFieldValue(index.column(), val)) return false;

		combatants.replace(row, cmbtnt);
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });
		return true;
	}
	return false;
}

bool CombatantModel::addCombatant(int row, const Combatant& cmbtnt, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginInsertRows(QModelIndex(), row, row);

	combatants.insert(row, cmbtnt);

	endInsertRows();
	emit dataChanged(index(row, 0), index(row, columnCount()), { Qt::DisplayRole, Qt::EditRole });
	return true;
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
		combatants.insert(row, Combatant());
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

const QVector<Combatant>& CombatantModel::getAllCombatants() const
{
	return combatants;
}

Combatant CombatantModel::getCombatantFromIndex(QModelIndex& index)
{
	return combatants.at(index.row());
}
