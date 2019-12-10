#include "EncounterManager.h"

EncounterManager::EncounterManager(QWidget* parent)
	: QMainWindow(parent),
	cmbtntModel(new CombatantModel(this)),
	proxyModel(new QSortFilterProxyModel(this))
{
	ui.setupUi(this);
	
	proxyModel->setSourceModel(cmbtntModel);
	proxyModel->setFilterKeyColumn(1);
	ui.combatantTableView->setModel(proxyModel);
}

void EncounterManager::on_addCombatantButton_clicked()
{
	AddCombatantDialog dialog(this);
	if (dialog.exec()) {
		addEntry(dialog.name(),
			dialog.initBonus(),
			dialog.maxHP(),
			dialog.isPlayer(),
			dialog.player());
	}
}

void EncounterManager::addEntry(QString& name, int initBonus, int maxHP, bool isPlayer, QString& player)
{
	cmbtntModel->insertRows(0, 1, QModelIndex());

	QModelIndex index = cmbtntModel->index(0, 0, QModelIndex());
	cmbtntModel->setData(index, name, Qt::EditRole);
	index = cmbtntModel->index(0, 1, QModelIndex());
	cmbtntModel->setData(index, initBonus, Qt::EditRole);
	index = cmbtntModel->index(0, 2, QModelIndex());
	cmbtntModel->setData(index, maxHP, Qt::EditRole);
	index = cmbtntModel->index(0, 3, QModelIndex());
	cmbtntModel->setData(index, isPlayer, Qt::EditRole);
	index = cmbtntModel->index(0, 4, QModelIndex());
	cmbtntModel->setData(index, player, Qt::EditRole);
}

void EncounterManager::on_combatantTableView_selectionChanged()
{
	ui.combatantTableView->update();
}

void EncounterManager::on_removeButton_clicked()
{
	QTableView* temp = static_cast<QTableView*>(ui.combatantTableView);
	QSortFilterProxyModel* proxy = static_cast<QSortFilterProxyModel*>(temp->model());
	QItemSelectionModel* selectionModel = temp->selectionModel();

	const QModelIndexList indexes = selectionModel->selectedRows();

	for (QModelIndex index : indexes) {
		int row = proxy->mapToSource(index).row();
		cmbtntModel->removeRows(row, 1, QModelIndex());
	}
}
