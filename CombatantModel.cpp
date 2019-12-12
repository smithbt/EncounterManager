#include "CombatantModel.h"

CombatantModel::CombatantModel(QObject *parent)
	: QAbstractTableModel(parent)
{
	curTurn = -1;
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
	// Columns: name, initRoll, initBonus, curHP, maxHP, isPlayer, playerName, other info
	return parent.isValid() ? 0 : 8; 
}

QVariant CombatantModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= combatants.size() || index.row() < 0)
		return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		const auto& cbt = combatants.at(index.row());
		switch (index.column()) {
		case NAME: return cbt.name;
		case INITIATIVE_ROLL: return cbt.initRoll;
		case INITIATIVE_BONUS: return cbt.initBonus;
		case CUR_HP: return cbt.curHP;
		case MAX_HP: return cbt.maxHP;
		case IS_PLAYER: return cbt.isPlayer;
		case PLAYER_NAME: return cbt.player;
		case OTHER_INFO: return cbt.otherInfo;
		default: break;
		}
	}
	else if (role == Qt::BackgroundColorRole && index.row() == curTurn)	{ 
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
		case NAME:
			return tr("Name");
		case INITIATIVE_ROLL:
			return tr("Initiative Roll");
		case INITIATIVE_BONUS:
			return tr("Initiative Bonus");
		case CUR_HP:
			return tr("Current HP");
		case MAX_HP:
			return tr("Max HP");
		case IS_PLAYER:
			return tr("PC?");
		case PLAYER_NAME:
			return tr("Player");
		case OTHER_INFO:
			return tr("Other Info");
		default:
			break;
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
		case NAME:
			cmbtnt.name = val.toString();
			break;
		case INITIATIVE_ROLL:
			cmbtnt.initRoll = val.toInt();
			break;
		case CUR_HP:
			cmbtnt.curHP = val.toInt();
			break;
		case MAX_HP:
			cmbtnt.maxHP = val.toInt();
			break;
		case IS_PLAYER: 
			cmbtnt.isPlayer = val.toBool();
			break;
		case PLAYER_NAME: 
			cmbtnt.player = val.toString();
			break;
		case INITIATIVE_BONUS:
			cmbtnt.initBonus = val.toInt();
			break;
		case OTHER_INFO:
			cmbtnt.otherInfo = val.toString();
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

void CombatantModel::setCurTurn(QModelIndex& nxt)
{
	curTurn = nxt.row();
}

QModelIndex CombatantModel::getCurrentTurnIndex()
{
	return index(curTurn, 0);
}

Combatant CombatantModel::getCombatantFromIndex(QModelIndex& index)
{
	return combatants.at(index.row());
}
