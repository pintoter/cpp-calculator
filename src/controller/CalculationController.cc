#include "CalculationController.h"

namespace s21 {
s21::CalculationController::CalculationController() noexcept {
  model_ = new CalculationModel();
}

s21::CalculationController::~CalculationController() { delete model_; }

void s21::CalculationController::SetInputStr(const std::string& line) noexcept {
  model_->SetStr(line);
}

bool s21::CalculationController::GetPolishBool() const noexcept {
  return model_->GetBool();
}

double s21::CalculationController::GetCalculatedExpression(
    const std::string& x_str) noexcept {
  QString temp = QString::fromStdString(model_->GetStr());

  if (temp.contains('x')) {
    std::string temp_x = x_str;

    if (!model_->GetStr().empty()) {
      model_->SetStr("");
    }

    std::string tmp_polish = "(" + temp_x + ")";
    temp_x = tmp_polish;
    temp.replace('x', QString::fromStdString(temp_x));
    model_->SetStr(temp.toStdString());
  }
  return model_->CalculateExpression();
};
}  // namespace s21