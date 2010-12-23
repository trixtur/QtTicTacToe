#include "tictactoe.h"

TicTacToe::TicTacToe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TicTacToe)
{
    ui->setupUi(this);
    connect(ui->actionE_xit, SIGNAL(triggered()),this,SLOT(close()));
    initialSetup = true;
    Reset();
    initialSetup = false;
}

TicTacToe::~TicTacToe()
{
    delete ui;
}

bool TicTacToe::isFull()
{
    if(ui->TopLeft_Button->text().isEmpty())
        return false;
    if(ui->TopMiddle_Button->text().isEmpty())
        return false;
    if(ui->TopRight_Button->text().isEmpty())
        return false;
    if(ui->MiddleLeft_Button->text().isEmpty())
        return false;
    if(ui->MiddleMiddle_Button->text().isEmpty())
        return false;
    if(ui->MiddleRight_Button->text().isEmpty())
        return false;
    if(ui->BottomLeft_Button->text().isEmpty())
        return false;
    if(ui->BottomMiddle_Button->text().isEmpty())
        return false;
    if(ui->BottomRight_Button->text().isEmpty())
        return false;
    return true;
}

void TicTacToe::Reset()
{
    QPushButton *b;

    b = ui->TopLeft_Button;
    SetButton(&b,"");
    ui->TopLeft_Button = b;

    b = ui->TopMiddle_Button;
    SetButton(&b,"");
    ui->TopMiddle_Button = b;

    b = ui->TopRight_Button;
    SetButton(&b,"");
    ui->TopRight_Button = b;

    b = ui->MiddleLeft_Button;
    SetButton(&b,"");
    ui->MiddleLeft_Button = b;

    b = ui->MiddleMiddle_Button;
    SetButton(&b,"");
    ui->MiddleMiddle_Button = b;

    b = ui->MiddleRight_Button;
    SetButton(&b,"");
    ui->MiddleRight_Button = b;

    b = ui->BottomLeft_Button;
    SetButton(&b,"");
    ui->BottomLeft_Button = b;

    b = ui->BottomMiddle_Button;
    SetButton(&b,"");
    ui->BottomMiddle_Button = b;

    b = ui->BottomRight_Button;
    SetButton(&b,"");
    ui->BottomRight_Button = b;

    connect(ui->TopLeft_Button, SIGNAL(pressed()),this,SLOT(PressTopLeft()));
    connect(ui->TopMiddle_Button, SIGNAL(pressed()),this,SLOT(PressTopMiddle()));
    connect(ui->TopRight_Button, SIGNAL(pressed()),this,SLOT(PressTopRight()));
    connect(ui->MiddleLeft_Button,SIGNAL(pressed()),this,SLOT(PressMiddleLeft()));
    connect(ui->MiddleMiddle_Button,SIGNAL(pressed()),this,SLOT(PressMiddleMiddle()));
    connect(ui->MiddleRight_Button,SIGNAL(pressed()),this,SLOT(PressMiddleRight()));
    connect(ui->BottomLeft_Button,SIGNAL(pressed()),this,SLOT(PressBottomLeft()));
    connect(ui->BottomMiddle_Button,SIGNAL(pressed()),this,SLOT(PressBottomMiddle()));
    connect(ui->BottomRight_Button,SIGNAL(pressed()),this,SLOT(PressBottomRight()));
    is_X = true;
}

void TicTacToe::RunButtonPress(QPushButton *b)
{
    int quad = -1;
    if(b == ui->TopLeft_Button)
        quad = 0;
    if(b == ui->TopMiddle_Button)
        quad = 1;
    if(b == ui->TopRight_Button)
        quad = 2;
    if(b == ui->MiddleLeft_Button)
        quad = 3;
    if(b == ui->MiddleMiddle_Button)
        quad = 4;
    if(b == ui->MiddleRight_Button)
        quad = 5;
    if(b == ui->BottomLeft_Button)
        quad = 6;
    if(b == ui->BottomMiddle_Button)
        quad = 7;
    if(b == ui->BottomRight_Button)
        quad = 8;

    if(is_X)
    {
        is_X = false;
        SetButton(&b,"X");
    }
    else
    {
        is_X = true;
       SetButton(&b,"O");
    }

    if(quad == 0)
        ui->TopLeft_Button = b;
    if(quad == 1)
        ui->TopMiddle_Button = b;
    if(quad == 2)
        ui->TopRight_Button = b;
    if(quad == 3)
        ui->MiddleLeft_Button = b;
    if(quad == 4)
        ui->MiddleMiddle_Button = b;
    if(quad == 5)
        ui->MiddleRight_Button = b;
    if(quad == 6)
        ui->BottomLeft_Button = b;
    if(quad == 7)
        ui->BottomMiddle_Button = b;
    if(quad == 8)
        ui->BottomRight_Button = b;

    if(isFull())
    {
        QMessageBox::Icon i = QMessageBox::Information;
        QMessageBox *b = new QMessageBox("CAT","The Game ended in a tie.",i,0,DIALOG_OK_BUTTON,0,this,Qt::MSWindowsFixedSizeDialogHint);
        b->show();
        connect(b,SIGNAL(finished(int)),this,SLOT(MBoxClose(int)));
    }
}

void TicTacToe::MBoxClose(int ret)
{
    if(ret == DIALOG_OK_BUTTON)
    {
        Reset();
    }
}

void TicTacToe::SetButton(QPushButton  **b, const QString &s)
{
    int x = (*b)->x();
    int y;
    if(initialSetup)
        y = (*b)->y() + ui->menuBar->size().height();
    else
        y = (*b)->y();
    int size_w = (*b)->size().width();
    int size_h = (*b)->size().height();
    delete *b;
    *b = 0;

    *b = new QPushButton(s,this);
    QFont *f = new QFont("MS Sans Serif",24,1,false);
    (*b)->setFont(*f);
    (*b)->move(x,y);
    (*b)->resize(size_w,size_h);
    (*b)->show();
}

void TicTacToe::PressTopLeft()
{
    RunButtonPress(ui->TopLeft_Button);
}

void TicTacToe::PressTopMiddle()
{
    RunButtonPress(ui->TopMiddle_Button);
}

void TicTacToe::PressTopRight()
{
    RunButtonPress(ui->TopRight_Button);
}

void TicTacToe::PressMiddleLeft()
{
    RunButtonPress(ui->MiddleLeft_Button);
}

void TicTacToe::PressMiddleMiddle()
{
    RunButtonPress(ui->MiddleMiddle_Button);
}

void TicTacToe::PressMiddleRight()
{
    RunButtonPress(ui->MiddleRight_Button);
}

void TicTacToe::PressBottomLeft()
{
    RunButtonPress(ui->BottomLeft_Button);
}

void TicTacToe::PressBottomMiddle()
{
    RunButtonPress(ui->BottomMiddle_Button);
}

void TicTacToe::PressBottomRight()
{
    RunButtonPress(ui->BottomRight_Button);
}
