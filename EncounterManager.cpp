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
		proxyModel->sort(Combatant::INITIATIVE_ROLL, Qt::DescendingOrder);
		curTurn = 0;
	} else { // Increment current turn
		QModelIndex cur = proxyModel->mapToSource(proxyModel->index(curTurn, Combatant::CURRENT_TURN));
		cmbtntModel->setData(cur, false);
		if (++curTurn >= cmbtntModel->rowCount()) curTurn = 0;
	}

	// update new current turn
	QModelIndex nxt = proxyModel->mapToSource(proxyModel->index(curTurn, Combatant::CURRENT_TURN));
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
		QModelIndex qmIdx = cmbtntModel->index(idx, Combatant::INITIATIVE_ROLL);
		int initRoll = D20 + cmbtnt.initBonus;
		cmbtntModel->setData(qmIdx, initRoll);

		// clear combatant's  current turn flag
		qmIdx = cmbtntModel->index(idx, Combatant::CURRENT_TURN);
		cmbtntModel->setData(qmIdx, false);
	}
	curTurn = -1; // reset turn flag
	nextTurn();
}

void EncounterManager::on_addCombatantButton_clicked()
{
	AddCombatantDialog dialog(this);
	if (dialog.exec()) {
		addEntry(dialog.getCombatant());
	}
}

void EncounterManager::addEntry(const Combatant& cmbtnt)
{
	cmbtntModel->addCombatant(0, cmbtnt);
}

void EncounterManager::on_removeButton_clicked()
{
	const QModelIndexList indexes = ui.combatantView->selectionModel()->selectedRows();

	for (QModelIndex index : indexes) {
		int row = proxyModel->mapToSource(index).row();
		cmbtntModel->removeRows(row, 1, QModelIndex());
	}
}

void EncounterManager::on_actionToggle_Info_triggered() 
{
	if (ui.currentCombatantWidget->isVisible()) {
		ui.currentCombatantWidget->setVisible(false);
		ui.actionToggle_Info->setText("Show Info");
	}
	else {
		ui.currentCombatantWidget->setVisible(true);
		ui.actionToggle_Info->setText("Hide Info");
	}
}
