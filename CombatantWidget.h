#pragma once

#include <QWidget>
#include <QDataWidgetMapper>
#include "ui_CombatantWidget.h"
#include "CombatantModel.h"

class CombatantWidget : public QWidget
{
	Q_OBJECT

public:
	CombatantWidget(QWidget *parent = Q_NULLPTR);
	CombatantWidget(QWidget* parent, QDataWidgetMapper* mapper);
	~CombatantWidget();

	void setMapper(QDataWidgetMapper* mapper);

private:
	Ui::CombatantWidget ui;
	QDataWidgetMapper* mapper;
};
