#pragma once

#include <QtWidgets/QDialog>
#include "ui_TeamTalkHP.h"

class TeamTalkHP : public QDialog
{
    Q_OBJECT

public:
    TeamTalkHP(QWidget *parent = nullptr);
    ~TeamTalkHP();

private:
    Ui::TeamTalkHPClass ui;
};
