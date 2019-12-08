#pragma once

#include <QtWidgets/QMainWindow>
#include <QListWidgetItem>
#include "ui_EncounterManager.h"
#include "AddCombatantDialog.h"
#include "ui_AddCombatantDialog.h"

class EncounterManager : public QMainWindow
{
	Q_OBJECT

public:
	EncounterManager(QWidget *parent = Q_NULLPTR);

private:
	Ui::EncounterManagerClass ui;

private slots:
	void on_addCombatantButton_clicked();
	void on_combatantList_currentItemChanged();
	void on_removeButton_clicked();
};
