#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");

    SetText("0");

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::RemoveTrailingZeroes(const QString &text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString MainWindow::NormalizeNumber(const QString &text) {
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}

void MainWindow::SetText(const QString& text) {

    if (equal_pressed_) {
        ui->l_formula->setText("");
    }

    QString text2 = NormalizeNumber(RemoveTrailingZeroes(text));
    input_number_ = text2;
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(text2);

}

void MainWindow::AddText(const QString& suffix) {

    input_number_ = input_number_ + suffix;
    SetText(input_number_);
}

void MainWindow::on_tb_one_clicked()
{
    AddText("1");
}

void MainWindow::on_tb_two_clicked()
{
    AddText("2");
}

void MainWindow::on_tb_three_clicked()
{
    AddText("3");
}

void MainWindow::on_tb_four_clicked()
{
    AddText("4");
}

void MainWindow::on_tb_five_clicked()
{
    AddText("5");
}

void MainWindow::on_tb_six_clicked()
{
    AddText("6");
}

void MainWindow::on_tb_seven_clicked()
{
    AddText("7");
}

void MainWindow::on_tb_eight_clicked()
{
    AddText("8");
}

void MainWindow::on_tb_nine_clicked()
{
    AddText("9");
}

void MainWindow::on_tb_zero_clicked()
{
    AddText("0");
}

void MainWindow::on_tb_comma_clicked()
{
    if (!comma_pressed_) {
        comma_pressed_ = true;
        if (equal_pressed_) {
            QString num = ui->l_result->text();
            if (!num.isEmpty()) {
                input_number_ = num;
            }
        }
        if (input_number_[input_number_.size() - 1] !=  '.') {
            AddText(".");
        }
    }

}

void MainWindow::on_tb_negate_clicked()
{

    QString num = ui->l_result->text();
    if (!num.isEmpty()) {
        input_number_ = num;
    } else {
        input_number_ = "0";
    }


    if (input_number_.startsWith("-")) {
        input_number_ = input_number_.mid(1);
        QString text = input_number_;
        SetText(text);
    } else {
        QString text = "-" + input_number_;
        SetText(text);
    }

}

void MainWindow::on_tb_backspace_clicked()
{
    if (!input_number_.isEmpty()) {
        input_number_.chop(1);
        SetText(input_number_);
    }
}

QString MainWindow::OpToString(Operation op) {
    switch(op) {
    case Operation::NO_OPERATION: return "";
    case Operation::ADDITION: return "+";
    case Operation::DIVISION: return "÷";
    case Operation::MULTIPLICATION: return "×";
    case Operation::SUBTRACTION: return "−";
    case Operation::POWER: return "^";
    default: return "";
    }
}

void MainWindow::SetOperation(Operation op) {
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);

    }
    current_operation_ = op;
    QString text = "%1 %2";
    QString textformatted = text.arg(calculator_.GetNumber()).arg(OpToString(op));
    ui->l_formula->setText(textformatted);
    input_number_ = "";
}

void MainWindow::on_tb_equal_clicked()
{
    equal_pressed_ = true;
    QString text = "%1 %2 %3 =";
    QString textformatted = text.arg(calculator_.GetNumber()).arg(OpToString(current_operation_)).arg(active_number_);
    ui->l_formula->setText(textformatted);
    switch (current_operation_) {
        case Operation::NO_OPERATION:
            return;
        case Operation::ADDITION:
            calculator_.Add(active_number_);
            break;
        case Operation::DIVISION:
            calculator_.Div(active_number_);
            break;
        case Operation::SUBTRACTION:
            calculator_.Sub(active_number_);
            break;
        case Operation::MULTIPLICATION:
            calculator_.Mul(active_number_);
            break;
        case Operation::POWER:
            calculator_.Pow(active_number_);
            break;
    }

    active_number_ = calculator_.GetNumber();
    ui->l_result->setText(QString::number(active_number_));
    input_number_ = "";
    current_operation_ = Operation::NO_OPERATION;
    comma_pressed_ = false;

}

void MainWindow::on_tb_add_clicked()
{
    SetOperation(Operation::ADDITION);
    equal_pressed_ = false;
    comma_pressed_ = false;

}

void MainWindow::on_tb_substract_clicked()
{
    SetOperation(Operation::SUBTRACTION);
    equal_pressed_ = false;
    comma_pressed_ = false;

}


void MainWindow::on_tb_multiplicate_clicked()
{
    SetOperation(Operation::MULTIPLICATION);
    equal_pressed_ = false;
    comma_pressed_ = false;

}

void MainWindow::on_tb_divide_clicked()
{
    SetOperation(Operation::DIVISION);
    equal_pressed_ = false;
    comma_pressed_ = false;

}

void MainWindow::on_tb_power_clicked()
{
    SetOperation(Operation::POWER);
    equal_pressed_ = false;
    comma_pressed_ = false;

}

void MainWindow::on_tb_reset_clicked()
{
    SetOperation(Operation::NO_OPERATION);
    ui->l_formula->setText("");
    equal_pressed_ = false;
    comma_pressed_ = false;
    SetText("0");
}

void MainWindow::on_tb_mc_clicked()
{
    number_is_saved_ = false;
    saved_number_ = 0;
    ui->l_memory->setText("");
}

void MainWindow::on_tn_mr_clicked()
{
    if (number_is_saved_) {
        active_number_ = saved_number_;
        ui->l_result->setText(QString::number(saved_number_));
        input_number_ = "";
    }
}

void MainWindow::on_tb_ms_clicked()
{
    number_is_saved_ = true;
    saved_number_ = active_number_;
    ui->l_memory->setText("M");
}

