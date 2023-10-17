#include <gtest/gtest.h>

#include "../model/CreditModel.h"

constexpr auto EPS = 1e-7;

TEST(credit_calculation_suite, annuity_payment) {
  s21::CreditModel model;
  model.CalculateAnnuity(100000, 12, 5);

  ASSERT_NEAR(model.GetAnnuityMonthlyPayment(), 8560.7481788, EPS);
  ASSERT_NEAR(model.GetOverpayment(), 2728.9781462, EPS);
  ASSERT_NEAR(model.GetTotalPayment(), 102728.9781462, EPS);
}

TEST(credit_calculation_suite, differential_payment) {
  s21::CreditModel model;
  model.CalculateDifferentiate(100000, 12, 5);

  ASSERT_NEAR(model.GetOverpayment(), 2708.3333333, EPS);
  ASSERT_NEAR(model.GetTotalPayment(), 102708.3333333, EPS);
}