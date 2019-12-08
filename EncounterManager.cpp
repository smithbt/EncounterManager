#include "EncounterManager.h"

EncounterManager::EncounterManager(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void EncounterManager::on_addCombatantButton_clicked()
{
	AddCombatantDialog dialog(this);
	if (dialog.exec()) {
		Combatant *cmbtnt = dialog.createCombatant();
		if (cmbtnt) QListWidgetItem* item = new QListWidgetItem(cmbtnt->getName(), ui.combatantList);
	}
}

void EncounterManager::on_combatantList_currentItemChanged()
{
	QListWidgetItem* curItem = ui.combatantList->currentItem();

	if (curItem) {
		ui.currentCombatant->setTitle(curItem->text());
	} else {
		ui.currentCombatant->setTitle("<no combatant selected>");
	}
}

void EncounterManager::on_removeButton_clicked()
{
}
