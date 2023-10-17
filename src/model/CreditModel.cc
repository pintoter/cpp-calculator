#include "CreditModel.h"

namespace s21 {
void CreditModel::CalculateAnnuity(const double& total_amount,
                                   const double& loan_term,
                                   const double& rate) noexcept {
  total_amount_ = total_amount;
  loan_term_ = loan_term;
  rate_ = rate;

  double i = rate_ / 12 / 100;
  double k =
      (i * pow((1 + i), (int)loan_term_)) / (pow((1 + i), (int)loan_term_) - 1);

  monthly_payment_ = k * total_amount_;

  total_payment_ = monthly_payment_ * (int)loan_term_;

  overpayment_ = total_payment_ - total_amount_;
}

void CreditModel::CalculateDifferentiate(const double& total_amount,
                                         const double& loan_term,
                                         const double& rate) noexcept {
  total_amount_ = total_amount;
  loan_term_ = loan_term;
  rate_ = rate;

  double monthly_rate = rate_ / 1200;
  double base_monthly_payment = total_amount_ / loan_term_;
  total_payment_ = 0;
  double first, last = 0;
  for (int i = 0; i < (int)loan_term_; ++i) {
    total_payment_ += base_monthly_payment +
                      (total_amount_ - base_monthly_payment * i) * monthly_rate;
    if (i == 0) {
      first = base_monthly_payment +
              (total_amount_ - base_monthly_payment * i) * monthly_rate;
    }

    if (i == (int)loan_term_ - 1) {
      last = base_monthly_payment +
             (total_amount_ - base_monthly_payment * i) * monthly_rate;
    }
  }
  overpayment_ = total_payment_ - total_amount_;
  diff_monthly_payment_ =
      ToPrecisedString(first, 2) + "..." + ToPrecisedString(last, 2);
}

double CreditModel::GetAnnuityMonthlyPayment() const noexcept {
  return monthly_payment_;
}

std::string CreditModel::GetDifferentiatedMonthlyPayment() const noexcept {
  return diff_monthly_payment_;
}

double CreditModel::GetTotalPayment() const noexcept { return total_payment_; }

double CreditModel::GetOverpayment() const noexcept { return overpayment_; }

std::string CreditModel::ToPrecisedString(double val, int precision) noexcept {
  std::stringstream ss;
  ss << std::setprecision(precision) << std::fixed << val;
  return ss.str();
};
}  // namespace s21