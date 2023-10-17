#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CREDITMODEL_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CREDITMODEL_H_

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace s21 {
    /*!
   * \brief Class for processing credit expressions
   */
class CreditModel {
 public:
   /*!
   * \brief Basic constructor for CreditModel
   */
  CreditModel() = default;
   /*!
   * \brief Destructor for CreditModel
   */
  ~CreditModel() = default;

  /*!
   * \brief Setter for annuity payment
   */
  void CalculateAnnuity(const double& total_amount, const double& loan_term,
                        const double& rate) noexcept;
  /*!
   * \brief Setter for annuity payment
   */
  void CalculateDifferentiate(const double& total_amount,
                              const double& loan_term,
                              const double& rate) noexcept;
  /*!
   * \brief Getter for annuity monthly payment
   */
  [[nodiscard]] double GetAnnuityMonthlyPayment() const noexcept;
    /*!
   * \brief Getter for differentiated monthly payment
   */
  [[nodiscard]] std::string GetDifferentiatedMonthlyPayment() const noexcept;
  /*!
   * \brief Getter for total payment
   */
  [[nodiscard]] double GetTotalPayment() const noexcept;
    /*!
   * \brief Getter for overpayment
   */
  [[nodiscard]] double GetOverpayment() const noexcept;
  std::string ToPrecisedString(double val, int precision) noexcept;

 private:
  double total_amount_ = 0;
  double loan_term_ = 0;
  double rate_ = 0;

  double monthly_payment_ = 0;
  double total_payment_ = 0;
  double overpayment_ = 0;

  std::string diff_monthly_payment_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_CREDITMODEL_H_