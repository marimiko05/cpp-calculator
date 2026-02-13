#pragma once
#include <string>

using Number = double;

bool ReadNumber(Number& result);
bool ReadRightNumber(Number& right_num);
std::string ReadOperation();
bool RunCalculatorCycle();