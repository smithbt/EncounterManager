#pragma once

#include <QWidget>
#include "ui_CombatantWidget.h"
#include "CombatantModel.h"

class CombatantWidget : public QWidget
{
	Q_OBJECT

public:
	CombatantWidget(QWidget *parent = Q_NULLPTR);
	~CombatantWidget();

public slots:
	void updateInfo(Combatant& cmbtnt);
	
private:
	Ui::CombatantWidget ui;
};
