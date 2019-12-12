#include "CombatantWidget.h"

CombatantWidget::CombatantWidget(QWidget* parent)
	: QWidget(parent),
	mapper(new QDataWidgetMapper(this))
{
	ui.setupUi(this);
}

CombatantWidget::CombatantWidget(QWidget *parent, QDataWidgetMapper* mapper)
	: QWidget(parent)
{
	ui.setupUi(this);
	setMapper(mapper);
}

CombatantWidget::~CombatantWidget()
{
}

void CombatantWidget::setMapper(QDataWidgetMapper* mapper)
{
	this->mapper = mapper;
	mapper->addMapping(ui.nameEdit, CombatantModel::NAME);
	mapper->addMapping(ui.isPlayerCheckBox, CombatantModel::IS_PLAYER, "checked");
	mapper->addMapping(ui.playerEdit, CombatantModel::PLAYER_NAME);
	mapper->addMapping(ui.curHPSpinBox, CombatantModel::CUR_HP);
	mapper->addMapping(ui.maxHPEdit, CombatantModel::MAX_HP);
	mapper->addMapping(ui.otherInfoEdit, CombatantModel::OTHER_INFO, "html");
}