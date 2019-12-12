#include "AddCombatantDialog.h"

AddCombatantDialog::AddCombatantDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

AddCombatantDialog::~AddCombatantDialog()
{
}

QString AddCombatantDialog::name() const
{
	return ui.nameEdit->text();
}

int AddCombatantDialog::initBonus() const
{
	return ui.initEdit->value();
}

int AddCombatantDialog::maxHP() const
{
	return ui.hpEdit->value();
}

bool AddCombatantDialog::isPlayer() const
{
	return ui.yesButton->isChecked();
}

QString AddCombatantDialog::player() const
{
	return ui.pcNameEdit->text();
}

QString AddCombatantDialog::otherInfo() const
{
	return ui.otherInfoEdit->toHtml();
}
