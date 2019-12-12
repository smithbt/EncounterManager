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

	mapper->setModel(proxyModel);
	connect(ui.combatantView->selectionModel(), &QItemSelectionModel::currentRowChanged, 
		mapper, &QDataWidgetMapper::setCurrentModelIndex);
	ui.currentCombatantWidget->setMapper(mapper);
}

void EncounterManager::nextTurn()
{
	QModelIndex curIdx = cmbtntModel->getCurrentTurnIndex();
	int nxtProxyRow = proxyModel->mapFromSource(curIdx).row() + 1;
	if (nxtProxyRow == cmbtntModel->rowCount()) nxtProxyRow = 0;
	QModelIndex nxt = proxyModel->mapToSource(proxyModel->index(nxtProxyRow, 0));
	cmbtntModel->setCurTurn(nxt);
	ui.combatantView->update();
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
		QModelIndex idx = cmbtntModel->index(combatants.indexOf(cmbtnt), CombatantModel::INITIATIVE_ROLL);
		int initRoll = D20 + cmbtnt.initBonus;
		cmbtntModel->setData(idx, initRoll);
	}
	ui.combatantView->model()->sort(CombatantModel::INITIATIVE_ROLL, Qt::DescendingOrder);
	cmbtntModel->setCurTurn(proxyModel->mapToSource(proxyModel->index(0, 0)));
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
