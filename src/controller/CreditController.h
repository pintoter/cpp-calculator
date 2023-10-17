#ifndef CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CREDITCONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CREDITCONTROLLER_H_

#include "../model/CreditModel.h"
#include "string"

namespace s21 {
  /*!
   * \brief Class for control credit expressions
   */
class CreditController {
 public:
  CreditController();
  ~CreditController();

  void CalculateAnnuity(const double& total_amount, const double& loan_term,
                        const double& rate) const;
  void CalculateDifferentiated(const double& total_amount,
                               const double& loan_term,
                               const double& rate) const;
  std::string GetAnnuityMonthlyPayment() noexcept;
  std::string GetDifferentiatedMonthlyPayment() const noexcept;
  std::string GetTotalPayment() noexcept;
  std::string GetOverpayment() noexcept;
  std::string ToPrecisedString(double val, int precision) noexcept;

 private:
  CreditModel* model_ = nullptr;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CREDITCONTROLLER_H_