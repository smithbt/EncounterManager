#pragma once

#include <QDialog>
#include <QFileDialog>
#include <QJsonDocument>
#include "ui_AddCombatantDialog.h"
#include "Combatant.h"

class AddCombatantDialog : public QDialog
{
	Q_OBJECT

public:
	AddCombatantDialog(QWidget *parent = Q_NULLPTR);
	~AddCombatantDialog();

	Combatant& getCombatant();

private:
	Ui::AddCombatantDialog ui;
	Combatant cmbtnt;

private slots:
	bool on_loadFileButton_clicked();
};
