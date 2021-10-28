#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <Windows.h>
#include <sys/stat.h>

bool isFileExists_stat(std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

LPWSTR stringToLPWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

std::string WCharToMByte(LPCWSTR lpcwszStr) {
	std::string str;
	DWORD dwMinSize = 0;
	LPSTR lpszStr = NULL;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, FALSE);
	if (0 == dwMinSize)
	{
		return FALSE;
	}
	lpszStr = new char[dwMinSize];
	WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, lpszStr, dwMinSize, NULL, FALSE);
	str = lpszStr;
	delete[] lpszStr;
	return str;
}

void create_ini_file_test(std::string ini_path= "./config.ini") {
	if (isFileExists_stat(ini_path) == false) {
		LPWSTR lpPath = stringToLPWSTR(ini_path);
		WritePrivateProfileStringW(L"TEST_APP", L"TEST", L"test", lpPath);
	}
	else {
		std::cout << "ini file already exist, continue..." << std::endl;
	}
}

void create_ini_file(std::string ini_path = "./config.ini") {
	if (isFileExists_stat(ini_path) == false) {
		std::ofstream File;
		File.open(ini_path);
		File.close();
	}
	else {
		std::cout << "ini file already exist, continue..." << std::endl;
	}
}

void write_ini_entry(std::string app_name, std::string key_name,std::string string_val,std::string ini_path = "./config.ini") {
	LPWSTR s1 = stringToLPWSTR(app_name);
	LPWSTR s2 = stringToLPWSTR(key_name);
	LPWSTR s3 = stringToLPWSTR(string_val);
	LPWSTR s4 = stringToLPWSTR(ini_path);
	if (isFileExists_stat(ini_path) == false) {
		std::cout << "ini file not exist" << std:: endl;
	}
	else {
		WritePrivateProfileStringW(s1, s2, s3, s4);
	}
}

std::string read_ini_entry(std::string app_name, std::string key_name, std::string default_val="NULL", std::string ini_path = "./config.ini") {
	LPWSTR s1 = stringToLPWSTR(app_name);
	LPWSTR s2 = stringToLPWSTR(key_name);
	LPWSTR s3 = stringToLPWSTR(default_val);
	LPWSTR s4 = stringToLPWSTR(ini_path);
	const int max_length = 1024;
	LPWSTR entry_val = new WCHAR[max_length];
	if (isFileExists_stat(ini_path) == false) {
		std::cout << "ini file not exist" << std::endl;
	}
	else {
		GetPrivateProfileStringW(s1, s2, s3, entry_val, max_length, s4);
	}
	std::cout << entry_val << std::endl;
	std::string entry_str = WCharToMByte(entry_val);
	delete entry_val;
	entry_val = nullptr;
	return entry_str;
}

/*
int mian() {
	std::string status_code;

	LPWSTR username = new WCHAR[20];
	LPWSTR password = new WCHAR[20];
	LPWSTR port = new WCHAR[10];
	LPWSTR root = new WCHAR[MAX_PATH];
	LPWSTR lpPath = L"./config.ini";
	lstrcpyW(username, L"user");
	lstrcpyW(password, L"user");
	lstrcpyW(port, L"21");
	lstrcpyW(root, L"E:\\tmp\\");
	std::string path_str = WCharToMByte(lpPath);

	if (isFileExists_stat(path_str) == false) {
		WritePrivateProfileStringW(L"CONFIG", L"Username", username, lpPath);
		WritePrivateProfileStringW(L"CONFIG", L"Password", password, lpPath);
		WritePrivateProfileStringW(L"CONFIG", L"Port", port, lpPath);
		WritePrivateProfileStringW(L"CONFIG", L"Root", root, lpPath);
		std::cout << "Generating file 'config.ini'" << std::endl;
	}
	else {
		GetPrivateProfileStringW(L"CONFIG", L"Username", L"user", username, 20, lpPath);
		GetPrivateProfileStringW(L"CONFIG", L"Password", L"user", password, 20, lpPath);
		GetPrivateProfileStringW(L"CONFIG", L"Port", L"21", port, 10, lpPath);
		GetPrivateProfileStringW(L"CONFIG", L"Root", L"E:\\tmp\\", root, MAX_PATH, lpPath);
		std::cout << "Reading file 'config.ini'" << std::endl;
	}
	std::string local_root = WCharToMByte(root); // The backslash at the end is necessary!
	int port_i = _wtoi(port);
	std::string username_s = WCharToMByte(username);
	std::string password_s = WCharToMByte(password);
}
*/