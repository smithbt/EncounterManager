#pragma once

#include <QtWidgets/QMainWindow>
#include <QSortFilterProxyModel>
#include <QDataWidgetMapper>
#include "ui_EncounterManager.h"
#include "AddCombatantDialog.h"
#include "CombatantModel.h"
#include "CombatantWidget.h"

#define D20 rand()%20+1

class EncounterManager : public QMainWindow
{
	Q_OBJECT

public:
	EncounterManager(QWidget *parent = Q_NULLPTR);
	void nextTurn();


private:
	Ui::EncounterManagerClass ui;
	CombatantModel* cmbtntModel;
	QSortFilterProxyModel* proxyModel;
	QDataWidgetMapper *mapper;

private slots:
	void on_nextButton_clicked();
	void on_addCombatantButton_clicked();
	void on_actionAdd_Combatant_triggered();
	void on_actionRemove_Combatant_triggered();
	void on_actionRoll_Initiative_triggered();
	void addEntry(QString& name, int initBonus, int maxHP, bool isPlayer, QString& player, QString& otherInfo);
	void on_removeButton_clicked();
	void on_actionShow_Info_triggered();
};
