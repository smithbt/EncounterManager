#pragma once

#include <QtWidgets/QMainWindow>
#include <QSortFilterProxyModel>
#include <QDataWidgetMapper>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QFileDialog>
#include "ui_EncounterManager.h"
#include "AddCombatantDialog.h"
#include "CombatantModel.h"
#include "CombatantWidget.h"
#include "Combatant.h"

#define D20 rand()%20+1

class EncounterManager : public QMainWindow
{
	Q_OBJECT

public:
	EncounterManager(QWidget *parent = Q_NULLPTR);

private:
	Ui::EncounterManagerClass ui;
	CombatantModel* cmbtntModel;
	QSortFilterProxyModel* proxyModel;
	QDataWidgetMapper *mapper;
	int curTurn;

	void addEntry(const Combatant& cmbtnt);
	void nextTurn();

private slots:
	void on_nextButton_clicked();
	void on_addCombatantButton_clicked();
	void on_actionAdd_Combatant_triggered();
	void on_actionRemove_Combatant_triggered();
	void on_actionRoll_Initiative_triggered();
	void on_removeButton_clicked();
	void on_actionToggle_Info_triggered();
	bool on_actionSave_triggered();
	bool on_actionSave_Encounter_triggered();
	bool on_actionLoad_Encounter_triggered();
};
