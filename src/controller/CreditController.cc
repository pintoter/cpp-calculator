#include "CreditController.h"

namespace s21 {

CreditController::CreditController() { model_ = new CreditModel; }

CreditController::~CreditController() { delete model_; }

void CreditController::CalculateAnnuity(const double& total_amount,
                                        const double& loan_term,
                                        const double& rate) const {
  model_->CalculateAnnuity(total_amount, loan_term, rate);
}

void CreditController::CalculateDifferentiated(const double& total_amount,
                                               const double& loan_term,
                                               const double& rate) const {
  model_->CalculateDifferentiate(total_amount, loan_term, rate);
}

std::string CreditController::GetAnnuityMonthlyPayment() noexcept {
  return ToPrecisedString(model_->GetAnnuityMonthlyPayment(), 2);
}

std::string CreditController::GetDifferentiatedMonthlyPayment() const noexcept {
  return model_->GetDifferentiatedMonthlyPayment();
}

std::string CreditController::GetTotalPayment() noexcept {
  return ToPrecisedString(model_->GetTotalPayment(), 2);
}

std::string CreditController::GetOverpayment() noexcept {
  return ToPrecisedString(model_->GetOverpayment(), 2);
}

std::string CreditController::ToPrecisedString(double val,
                                               int precision) noexcept {
  std::stringstream ss;
  ss << std::setprecision(precision) << std::fixed << val;
  return ss.str();
};
}  // namespace s21