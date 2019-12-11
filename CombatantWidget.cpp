#include "CombatantWidget.h"

CombatantWidget::CombatantWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

CombatantWidget::~CombatantWidget()
{
}

void CombatantWidget::updateInfo(Combatant& cmbtnt)
{
	// Name
	ui.nameLabel->setText(cmbtnt.name);
	
	// Player info (if applicable)
	ui.playerLabel->setVisible(cmbtnt.isPlayer);
	ui.playerLine->setVisible(cmbtnt.isPlayer);
	ui.playerLabel->setText(cmbtnt.player);

	// HP
	ui.maxHPEdit->setText(QString(cmbtnt.maxHP));
}