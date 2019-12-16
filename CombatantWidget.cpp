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
	mapper->addMapping(ui.nameEdit, Combatant::NAME);
	mapper->addMapping(ui.isPlayerCheckBox, Combatant::IS_PLAYER, "checked");
	mapper->addMapping(ui.playerEdit, Combatant::PLAYER_NAME);
	mapper->addMapping(ui.curHPSpinBox, Combatant::CUR_HP);
	mapper->addMapping(ui.maxHPEdit, Combatant::MAX_HP);
	mapper->addMapping(ui.otherInfoEdit, Combatant::OTHER_INFO, "html");
	mapper->addMapping(ui.initRollEdit, Combatant::INITIATIVE_ROLL);
	mapper->addMapping(ui.initBonusEdit, Combatant::INITIATIVE_BONUS);
}