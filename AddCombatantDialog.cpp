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
		cmbtnt.name = ui.nameEdit->text();
		cmbtnt.initBonus = ui.initEdit->value();
		cmbtnt.maxHP = ui.hpEdit->value();
		cmbtnt.isPlayer = ui.yesButton->isChecked();
		cmbtnt.player = ui.pcNameEdit->text();
		cmbtnt.otherInfo = ui.otherInfoEdit->toHtml();
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
