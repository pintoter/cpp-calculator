#include "loancalc.h"

#include "ui_loancalc.h"

LoanCalc::LoanCalc(QWidget *parent) noexcept
    : QMainWindow(parent), ui(new Ui::LoanCalc) {
  ui->setupUi(this);
  connect(ui->pushButton_closeLoan, SIGNAL(clicked()), this,
          SLOT(OnPushButtonCloseLoanClicked()));
  connect(ui->pushButton_calculate, SIGNAL(clicked()), this,
          SLOT(OnPushButtonCalculateClicked()));
}

LoanCalc::~LoanCalc() {
  delete ui;
  delete controller_;
}

void LoanCalc::OnPushButtonCloseLoanClicked() noexcept {
  close();
  emit loanMainWindow();
}

void LoanCalc::OnPushButtonCalculateClicked() noexcept {
  double total_amount = ui->lineEdit_totalAmount->text().toDouble();
  double loan_term = ui->lineEdit_loanTerm->text().toDouble();
  double rate = ui->lineEdit_ineterstRate->text().toDouble();
  if (total_amount > 0 && loan_term > 0) {
    if (rate > 0) {
      if (ui->radioButton_annuity->isChecked()) {
        controller_->CalculateAnnuity(total_amount, loan_term, rate);
        ui->lineEdit_paymentPerMonth->setText(
            QString::fromStdString(controller_->GetAnnuityMonthlyPayment()));
        ui->lineEdit_overpayment->setText(
            QString::fromStdString(controller_->GetOverpayment()));
        ui->lineEdit_totalPayment->setText(
            QString::fromStdString(controller_->GetTotalPayment()));
      } else if (ui->radioButton_differential->isChecked()) {
        controller_->CalculateDifferentiated(total_amount, loan_term, rate);
        ui->lineEdit_paymentPerMonth->setText(QString::fromStdString(
            controller_->GetDifferentiatedMonthlyPayment()));
        ui->lineEdit_overpayment->setText(
            QString::fromStdString(controller_->GetOverpayment()));
        ui->lineEdit_totalPayment->setText(
            QString::fromStdString(controller_->GetTotalPayment()));
      }
    } else {
      double payment = total_amount / loan_term;
      ui->lineEdit_paymentPerMonth->setText(QString::number(payment, 'g', 7));
      ui->lineEdit_overpayment->setText("0");
      ui->lineEdit_totalPayment->setText(QString::number(total_amount, 'g', 7));
    }
  } else {
    ui->lineEdit_paymentPerMonth->setText("0");
    ui->lineEdit_overpayment->setText("0");
    ui->lineEdit_totalPayment->setText("0");
  }
}