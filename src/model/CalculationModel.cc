#include "CalculationModel.h"

namespace s21 {
double s21::CalculationModel::CalculateExpression() {
  ConvertToPolish_();

  if (incorrect_expression_) {
    return 0;
  }

  double result = 0;
  std::stack<double> st;
  char* c_postfix = const_cast<char*>(input_string_.c_str());
  char* current_lexem = strtok(c_postfix, " ");

  while (current_lexem) {
    if (isdigit(current_lexem[0])) {
      st.push(atof(current_lexem));
    } else if (IsOperator_(current_lexem[0])) {
      CalculateOperation_(st, current_lexem[0]);
    } else if (IsFunction_(current_lexem[0])) {
      CalculateFunction_(st, current_lexem[0]);
    } else {
      incorrect_expression_ = true;
    }
    current_lexem = strtok(nullptr, " ");
  }

  SafeTop_(st);

  if (!incorrect_expression_) {
    result = st.top();
  }

  SafePop_(st);

  return result;
}

void s21::CalculationModel::CalculateOperation_(std::stack<double>& st,
                                                char ch) {
  double temp1 = 0;

  SafeTop_(st);

  if (!incorrect_expression_) {
    temp1 = st.top();
  }

  SafePop_(st);

  double temp2 = 0;

  SafeTop_(st);

  if (!incorrect_expression_) {
    temp2 = st.top();
  }

  SafePop_(st);

  if (incorrect_expression_) {
    return;
  }

  switch (ch) {
    case '%':
      st.push(temp1 * temp2 / 100);
      break;
    case '^':
      st.push(pow(temp2, temp1));
      break;
    case '+':
      st.push(temp2 + temp1);
      break;
    case '-':
      st.push(temp2 - temp1);
      break;
    case '*':
      st.push((temp2 * temp1));
      break;
    case 'm':
      st.push(fmod(temp2, temp1));
      break;
    case '/':
      st.push(temp2 / temp1);
      break;
    default:
      incorrect_expression_ = true;
      break;
  }
}

void s21::CalculationModel::CalculateFunction_(std::stack<double>& st,
                                               char ch) {
  double temp = st.top();

  SafePop_(st);

  if (incorrect_expression_) {
    return;
  }

  switch (ch) {
    case 'l':
      st.push(log(temp));
      break;
    case 's':
      st.push(sin(temp));
      break;
    case 'c':
      st.push(cos(temp));
      break;
    case 't':
      st.push(tan(temp));
      break;
    case 'S':
      st.push(asin(temp));
      break;
    case 'C':
      st.push(acos(temp));
      break;
    case 'T':
      st.push(atan(temp));
      break;
    case 'Q':
      st.push(sqrt(temp));
      break;
    case 'L':
      st.push(log10(temp));
      break;
    default:
      incorrect_expression_ = true;
      break;
  }
}

void s21::CalculationModel::ConvertToPolish_() {
  input_string_ = CheckExp_(input_string_);
  input_string_ = StrToTokens_(input_string_);

  if (incorrect_expression_) {
    return;
  }

  std::stack<char> st;
  std::string postfix_expression;
  char* c_input = const_cast<char*>(input_string_.c_str());
  char* current_lexem = strtok(c_input, " ");

  while (current_lexem) {
    std::string tmp_prev = postfix_expression;

    if (isdigit(current_lexem[0]) || current_lexem[0] == '.' ||
        current_lexem[0] == 'x') {
      postfix_expression += current_lexem;
    } else if (current_lexem[0] == '(' || IsFunction_(current_lexem[0])) {
      st.push(current_lexem[0]);
    } else if (current_lexem[0] == ')') {
      RightBracket_(st, postfix_expression);
    } else if (IsOperator_(current_lexem[0])) {
      Operator_(st, postfix_expression, current_lexem);
    }

    current_lexem = strtok(nullptr, " ");

    if (current_lexem && tmp_prev != postfix_expression) {
      postfix_expression += " ";
    }
  }

  while (!st.empty() && st.top() != '(') {
    if (postfix_expression[postfix_expression.length() - 1] != ' ')
      postfix_expression += " ";
    postfix_expression += st.top();
    st.pop();
  }

  if (!st.empty()) {
    incorrect_expression_ = true;
  }

  input_string_ = postfix_expression;
}

void s21::CalculationModel::RightBracket_(std::stack<char>& st,
                                          std::string& postfix_expression) {
  while (!st.empty() && st.top() != '(') {
    postfix_expression += st.top();
    st.pop();
    if (!st.empty() && st.top() != '(') postfix_expression += " ";
  }
  SafePop_(st);
}

void s21::CalculationModel::Operator_(std::stack<char>& st,
                                      std::string& postfix_expression,
                                      char* current_lexem) {
  while (!st.empty() && st.top() != '(' &&
         Priority_(st.top()) >= Priority_(current_lexem[0])) {
    postfix_expression += st.top();
    st.pop();

    if (!st.empty() && st.top() != '(' &&
        Priority_(st.top()) >= Priority_(current_lexem[0])) {
      postfix_expression += " ";
    }
  }

  st.push(current_lexem[0]);
}

void s21::CalculationModel::CorrectBrackets_(const std::string& input,
                                             const int& i) {
  if (input[i] == '(') {
    if (i - 1 >= 0 && (isdigit(input[i - 1]) || input[i - 1] == 'x')) {
      incorrect_expression_ = true;
    }
  } else {
    if (i + 1 < (int)input.length() &&
        (isdigit(input[i + 1]) || isalpha(input[i + 1]))) {
      incorrect_expression_ = true;
    }
  }
}

std::string s21::CalculationModel::StrToTokens_(const std::string& input) {
  bool contains_x_or_number = false;
  std::string temp = input;

  if (!input_string_.empty()) {
    input_string_.clear();
  }

  for (size_t i = 0; i < temp.length(); ++i) {
    if (temp.substr(i, 3) == "sin") {
      input_string_ += "s";
      i += 2;
    } else if (temp.substr(i, 3) == "cos") {
      input_string_ += "c";
      i += 2;
    } else if (temp.substr(i, 3) == "tan") {
      input_string_ += "t";
      i += 2;
    } else if (temp.substr(i, 3) == "mod") {
      input_string_ += "m";
      i += 2;
    } else if (temp.substr(i, 3) == "log") {
      input_string_ += "L";
      i += 2;
    } else if (temp.substr(i, 2) == "ln") {
      input_string_ += "l";
      i += 1;
    } else if (temp.substr(i, 4) == "asin") {
      input_string_ += "S";
      i += 3;
    } else if (temp.substr(i, 4) == "acos") {
      input_string_ += "C";
      i += 3;
    } else if (temp.substr(i, 4) == "atan") {
      input_string_ += "T";
      i += 3;
    } else if (temp.substr(i, 4) == "sqrt") {
      input_string_ += "Q";
      i += 3;
    } else if (isdigit(temp[i]) || temp[i] == '.') {
      NumToStr_(input_string_, temp, i);
      contains_x_or_number = true;
    } else if (IsOperator_(temp[i]) || temp[i] == 'x' || temp[i] == '(' ||
               temp[i] == ')') {
      if (temp[i] == 'x') {
        input_string_ += "( x )";
      } else if (temp[i] == '(' || temp[i] == ')') {
        CorrectBrackets_(temp, i);
        input_string_ += temp[i];
      } else if (temp[i] == '-' &&
                 (i == 0 || (!isdigit(temp[i - 1]) && temp[i - 1] != ')'))) {
        input_string_ += "0 -";
      } else {
        input_string_ += temp[i];
      }
      contains_x_or_number = true;
    } else {
      incorrect_expression_ = true;
    }

    if (i < temp.length() - 1) {
      input_string_ += " ";
    }
  }

  if (!contains_x_or_number) {
    incorrect_expression_ = true;
  }

  return input_string_;
}

std::string s21::CalculationModel::CheckExp_(const std::string& input) {
  std::string temp = input;
  std::string num = "";
  for (int i = 0; i < (int)input.length(); ++i) {
    if (input[i] == 'e') {
      if (input[i + 1] == '-')
        temp.replace(temp.find("e-"), 2, "/10^");
      else
        temp.replace(temp.find('e'), 1, "*10^");
    }
  }
  return temp;
}

bool s21::CalculationModel::IsOperator_(char ch) noexcept {
  return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' ||
          ch == 'm' || ch == '%');
}

void s21::CalculationModel::NumToStr_(std::string& result_str,
                                      const std::string& input, size_t& i) {
  if (isdigit(input[i])) {
    int dot_counter = 0;

    while (isdigit(input[i]) || input[i] == '.') {
      if (input[i] == '.') {
        ++dot_counter;
      }

      result_str += input[i++];
    }

    if (dot_counter > 1) {
      incorrect_expression_ = true;
    }
  } else {
    result_str += "0.";

    while (isdigit(input[++i])) {
      result_str += input[i];
    }
  }
  --i;
}

bool s21::CalculationModel::IsFunction_(char ch) noexcept {
  return (ch == 's' || ch == 'S' || ch == 'c' || ch == 'C' || ch == 't' ||
          ch == 'T' || ch == 'l' || ch == 'L' || ch == 'Q');
}

int s21::CalculationModel::Priority_(char op) noexcept {
  int result = kErr;
  switch (op) {
    case '+':
    case '-':
      result = kOp1;
      break;
    case '*':
    case '/':
    case '%':
    case 'm':
      result = kOp2;
      break;
    case 's':
    case 'S':
    case 'c':
    case 'C':
    case 't':
    case 'T':
    case 'l':
    case 'L':
    case 'Q':
      result = kOp3;
      break;
    case '^':
      result = kOp4;
      break;
    default:
      incorrect_expression_ = true;
      break;
  }
  return result;
};
}  // namespace s21