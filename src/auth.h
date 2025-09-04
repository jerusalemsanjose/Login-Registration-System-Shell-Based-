#pragma once
#include <string>

void registerUser();
void loginUser();
void changeUsername(const std::string& username);
void changePassword(const std::string& username);
void SetColor(int textColor, int bgColor);