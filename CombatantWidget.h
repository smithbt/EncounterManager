#pragma once

#include <QWidget>
#include "ui_CombatantWidget.h"

class CombatantWidget : public QWidget
{
	Q_OBJECT

public:
	CombatantWidget(QWidget *parent = Q_NULLPTR);
	~CombatantWidget();

private:
	Ui::CombatantWidget ui;
};
