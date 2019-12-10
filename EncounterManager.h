#pragma once

#include <QtWidgets/QMainWindow>
#include <QSortFilterProxyModel>
#include "ui_EncounterManager.h"
#include "AddCombatantDialog.h"
#include "CombatantModel.h"

class EncounterManager : public QMainWindow
{
	Q_OBJECT

public:
	EncounterManager(QWidget *parent = Q_NULLPTR);

private:
	Ui::EncounterManagerClass ui;
	CombatantModel* cmbtntModel;
	QSortFilterProxyModel* proxyModel;

private slots:
	void on_addCombatantButton_clicked();
	void addEntry(QString &name, int initBonus, int maxHP, bool isPlayer, QString &player);
	void on_combatantTableView_selectionChanged();
	void on_removeButton_clicked();
};
