#include "EncounterManager.h"

EncounterManager::EncounterManager(QWidget* parent)
	: QMainWindow(parent),
	cmbtntModel(new CombatantModel(this)),
	proxyModel(new QSortFilterProxyModel(this)),
	mapper(new QDataWidgetMapper(this))
{
	ui.setupUi(this);

	proxyModel->setSourceModel(cmbtntModel);
	ui.combatantView->setModel(proxyModel);
	curTurn = -1;

	mapper->setModel(proxyModel);
	connect(ui.combatantView->selectionModel(), &QItemSelectionModel::currentRowChanged, 
		mapper, &QDataWidgetMapper::setCurrentModelIndex);
	ui.currentCombatantWidget->setMapper(mapper);
}

void EncounterManager::nextTurn()
{
	if (curTurn == -1) { // encounter not yet started. Sort initiatives and begin
		proxyModel->sort(CombatantModel::INITIATIVE_ROLL, Qt::DescendingOrder);
		curTurn = 0;
	} else { // Increment current turn
		QModelIndex cur = proxyModel->mapToSource(proxyModel->index(curTurn, CombatantModel::CURRENT_TURN));
		cmbtntModel->setData(cur, false);
		if (++curTurn >= cmbtntModel->rowCount()) curTurn = 0;
	}

	// update new current turn
	QModelIndex nxt = proxyModel->mapToSource(proxyModel->index(curTurn, CombatantModel::CURRENT_TURN));
	cmbtntModel->setData(nxt, true);
}

void EncounterManager::on_nextButton_clicked()
{
	nextTurn();
}

void EncounterManager::on_actionAdd_Combatant_triggered()
{
	on_addCombatantButton_clicked();
}

void EncounterManager::on_actionRemove_Combatant_triggered()
{
	on_removeButton_clicked();
}

void EncounterManager::on_actionRoll_Initiative_triggered()
{
	QVector<Combatant> combatants = cmbtntModel->getAllCombatants();
	for (Combatant cmbtnt : combatants) {
		int idx = combatants.indexOf(cmbtnt);

		// update stored roll
		QModelIndex qmIdx = cmbtntModel->index(idx, CombatantModel::INITIATIVE_ROLL);
		int initRoll = D20 + cmbtnt.initBonus;
		cmbtntModel->setData(qmIdx, initRoll);

		// clear combatant's  current turn flag
		qmIdx = cmbtntModel->index(idx, CombatantModel::CURRENT_TURN);
		cmbtntModel->setData(qmIdx, false);
	}
	curTurn = -1; // reset turn flag
	nextTurn();
}

void EncounterManager::on_addCombatantButton_clicked()
{
	AddCombatantDialog dialog(this);
	if (dialog.exec()) {
		addEntry(dialog.name(),
			dialog.initBonus(),
			dialog.maxHP(),
			dialog.isPlayer(),
			dialog.player(),
			dialog.otherInfo());
	}
}

void EncounterManager::addEntry(QString& name, int initBonus, int maxHP, bool isPlayer, QString& player, QString& otherInfo)
{
	cmbtntModel->insertRows(0, 1, QModelIndex());

	QModelIndex index = cmbtntModel->index(0, CombatantModel::NAME, QModelIndex());
	cmbtntModel->setData(index, name, Qt::EditRole);
	index = cmbtntModel->index(0, CombatantModel::INITIATIVE_BONUS, QModelIndex());
	cmbtntModel->setData(index, initBonus, Qt::EditRole);
	index = cmbtntModel->index(0, CombatantModel::MAX_HP, QModelIndex());
	cmbtntModel->setData(index, maxHP, Qt::EditRole);
	index = cmbtntModel->index(0, CombatantModel::CUR_HP, QModelIndex());
	cmbtntModel->setData(index, maxHP, Qt::EditRole);
	index = cmbtntModel->index(0, CombatantModel::IS_PLAYER, QModelIndex());
	cmbtntModel->setData(index, isPlayer, Qt::EditRole);
	index = cmbtntModel->index(0, CombatantModel::PLAYER_NAME, QModelIndex());
	cmbtntModel->setData(index, player, Qt::EditRole);
	index = cmbtntModel->index(0, CombatantModel::OTHER_INFO, QModelIndex());
	cmbtntModel->setData(index, otherInfo, Qt::EditRole);
}

void EncounterManager::on_removeButton_clicked()
{
	const QModelIndexList indexes = ui.combatantView->selectionModel()->selectedRows();

	for (QModelIndex index : indexes) {
		int row = proxyModel->mapToSource(index).row();
		cmbtntModel->removeRows(row, 1, QModelIndex());
	}
}

void EncounterManager::on_actionShow_Info_triggered() 
{
	ui.currentCombatantWidget->setVisible(!ui.currentCombatantWidget->isVisible());
}
