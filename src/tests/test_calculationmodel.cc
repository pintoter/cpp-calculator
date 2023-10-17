#include "../model/CalculationModel.h"
#include <gtest/gtest.h>

TEST(CalculationModel, Default1) {
    std::string expression = "1+1";
    s21::CalculationModel model;
    model.SetStr(expression);
    double my_result = model.CalculateExpression();
    double original_result = 1 + 1;
    EXPECT_DOUBLE_EQ(my_result, original_result);
}

TEST(CalculationModel, Default2) {
    std::string expression = "sin(cos(10^2))*43.1+sqrt(625)*(sin(4)+43.143*log(100)-asin(0.4243))/ln(sin(14.03))*sqrt(0.1)/0.009^(-3)";
    s21::CalculationModel model;
    model.SetStr(expression);
    double my_result = model.CalculateExpression();
    double original_result = sin(cos(pow(10, 2)))*43.1+sqrt(625)*(sin(4)+43.143*log10(100)-asin(0.4243))/log(sin(14.03))*sqrt(0.1)/pow(0.009, -3);
    EXPECT_DOUBLE_EQ(my_result, original_result);
}

TEST(CalculationModel, Default3) {
    std::string expression = "sin(cos(10^2))*43.1+sqrt(625)*(sin(4)+43.143*log(100)-asin(0.4243))/ln(sin(14.03))*sqrt(0.1)";
    s21::CalculationModel model;
    model.SetStr(expression);
    double my_result = model.CalculateExpression();
    double original_result = sin(cos(pow(10, 2)))*43.1+sqrt(625)*(sin(4)+43.143*log10(100)-asin(0.4243))/log(sin(14.03))*sqrt(0.1);
    EXPECT_DOUBLE_EQ(my_result, original_result);
}

TEST(CalculationModel, Default4) {
    std::string expression = "atan(acos(0.1%50))";
    s21::CalculationModel model;
    model.SetStr(expression);
    double my_result = model.CalculateExpression();
    double original_result = atan(acos(0.1 * 0.5));
    EXPECT_DOUBLE_EQ(my_result, original_result);
}

TEST(CalculationModel, Default5) {
    std::string expression = "10mod2";
    s21::CalculationModel model;
    model.SetStr(expression);
    double my_result = model.CalculateExpression();
    double original_result = 10 % 2;
    EXPECT_DOUBLE_EQ(my_result, original_result);
}

TEST(CalculationModel, Exp1) {
    std::string expression = "tan(sqrt(1e3))";
    s21::CalculationModel model;
    model.SetStr(expression);
    double my_result = model.CalculateExpression();
    double original_result = tan(sqrt(1e3));
    EXPECT_DOUBLE_EQ(my_result, original_result);
}

TEST(CalculationModel, Exp2) {
    std::string expression = "1e-3+0.1+.1";
    s21::CalculationModel model;
    model.SetStr(expression);
    double my_result = model.CalculateExpression();
    double original_result = 1e-3 + 0.1 + .1;
    EXPECT_DOUBLE_EQ(my_result, original_result);
}

TEST(CalculationModel, Exp3) {
    std::string expression = "(1e-3+0.1+.1)^(-1e1)";
    s21::CalculationModel model;
    model.SetStr(expression);
    double my_result = model.CalculateExpression();
    double original_result = pow((1e-3 + 0.1 + .1), -1e1);
    EXPECT_DOUBLE_EQ(my_result, original_result);
}

TEST(CalculationModel, IncorrectExpression) {
    std::string expression = "(1e-3+0.1+.1)^=--1e1)";
    s21::CalculationModel model;
    model.SetStr(expression);
    model.CalculateExpression();
    bool is_incorrect = model.GetBool();
    EXPECT_TRUE(is_incorrect);
}

TEST(CalculationModel, IncorrectExpression2) {
    std::string expression = "sin";
    s21::CalculationModel model;
    model.SetStr(expression);
    model.CalculateExpression();
    bool is_incorrect = model.GetBool();
    EXPECT_TRUE(is_incorrect);
}