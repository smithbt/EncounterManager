#pragma once

#include <QDialog>
#include "ui_AddCombatantDialog.h"
#include "CombatantModel.h"

class AddCombatantDialog : public QDialog
{
	Q_OBJECT

public:
	AddCombatantDialog(QWidget *parent = Q_NULLPTR);
	~AddCombatantDialog();

	QString name() const;
	int initBonus() const;
	int maxHP() const;
	bool isPlayer() const;
	QString player() const;

private:
	Ui::AddCombatantDialog ui;
};
