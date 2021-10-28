#pragma once
#include <string>

bool isFileExists_stat(std::string& name);
void create_ini_file(std::string ini_path = "./config.ini");
void write_ini_entry(std::string app_name, std::string key_name, std::string string_val, std::string ini_path = "./config.ini");
std::string read_ini_entry(std::string app_name, std::string key_name, std::string default_val, std::string ini_path = "./config.ini");

LPWSTR stringToLPWSTR(std::string orig);
std::string WCharToMByte(LPCWSTR lpcwszStr);