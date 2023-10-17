#ifndef CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CALCULATIONCONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CALCULATIONCONTROLLER_H_

#include <QString>

#include "../model/CalculationModel.h"

namespace s21 {
      /*!
   * \brief Class for control calculation expressions
   */
class CalculationController {
 public:
  CalculationController() noexcept;
  ~CalculationController();

  void SetInputStr(const std::string& line) noexcept;
  bool GetPolishBool() const noexcept;
  double GetCalculatedExpression(const std::string& x_str) noexcept;

 private:
  CalculationModel* model_ = nullptr;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_CALCULATIONCONTROLLER_H_
