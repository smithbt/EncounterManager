#pragma once

#include <QDialog>
#include "ui_AddCombatantDialog.h"
#include "Combatant.h"

class AddCombatantDialog : public QDialog
{
	Q_OBJECT

public:
	AddCombatantDialog(QWidget *parent = Q_NULLPTR);
	~AddCombatantDialog();

	Combatant *createCombatant();

private:
	Ui::AddCombatantDialog ui;
};
