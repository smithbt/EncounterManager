#include "AddCombatantDialog.h"

AddCombatantDialog::AddCombatantDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

AddCombatantDialog::~AddCombatantDialog()
{
}

Combatant *AddCombatantDialog::createCombatant()
{
	QString player = ui.playerEdit->text();
	bool isPlayer = !player.isEmpty();
	QString name = ui.nameEdit->text();
	int initBonus = ui.initEdit->value();
	int hp = ui.hpEdit->value();

	if (!name.isEmpty()) {
		Combatant* cmbtnt = new Combatant(name,isPlayer);
		return cmbtnt;
	}
	else return nullptr;
	
}