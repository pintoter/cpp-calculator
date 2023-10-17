#ifndef LOANCALC_H
#define LOANCALC_H

#include <QMainWindow>
#include <QtMath>

#include "../controller/CreditController.h"

namespace Ui {
class LoanCalc;
}

class LoanCalc : public QMainWindow {
  Q_OBJECT

 public:
  explicit LoanCalc(QWidget *parent = nullptr) noexcept;
  ~LoanCalc();

 signals:
  void loanMainWindow();

 private slots:
  void OnPushButtonCloseLoanClicked() noexcept;
  void OnPushButtonCalculateClicked() noexcept;

 private:
  Ui::LoanCalc *ui;
  s21::CreditController *controller_ = new s21::CreditController;
  ;
};

#endif  // LOANCALC_H