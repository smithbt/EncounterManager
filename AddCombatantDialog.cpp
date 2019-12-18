#include "AddCombatantDialog.h"

AddCombatantDialog::AddCombatantDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	cmbtnt = Combatant();
}

AddCombatantDialog::~AddCombatantDialog()
{
}

Combatant& AddCombatantDialog::getCombatant()
{
	if (cmbtnt.isEmpty()) {
		cmbtnt.setFieldValue(Combatant::NAME, ui.nameEdit->text());
		cmbtnt.setFieldValue(Combatant::INITIATIVE_BONUS, ui.initEdit->value());
		cmbtnt.setFieldValue(Combatant::MAX_HP, ui.hpEdit->value());
		cmbtnt.setFieldValue(Combatant::IS_PLAYER, ui.yesButton->isChecked());
		cmbtnt.setFieldValue(Combatant::PLAYER_NAME, ui.pcNameEdit->text());
		cmbtnt.setFieldValue(Combatant::OTHER_INFO, ui.otherInfoEdit->toHtml());
	}
	return cmbtnt;
}

bool AddCombatantDialog::on_loadFileButton_clicked() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "..", tr("JSON Files (*.json)"));
	QFile loadFile(fileName);

	if (!loadFile.open(QIODevice::ReadOnly)) {
		qWarning("Could not open file.");
		return false;
	}

	QByteArray cmbtntData = loadFile.readAll();

	QJsonDocument loadDoc(QJsonDocument::fromJson(cmbtntData));

	cmbtnt.read(loadDoc.object());
	return true;
}
