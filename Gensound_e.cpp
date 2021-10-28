#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <ctype.h>
#include <Windows.h>
#include "iniHelper.h"
using namespace std;

string ini_path = "./config.ini";
unsigned short option = 0;
const int max_length = 1024;

unsigned short BPM = 185;
double INR = 60.0 / BPM;
unsigned short KeyUpDelay = 5;
string score =  "HJQJQEJ_________DHGHQG__________"
				"FDFDFQD_________QQJFFJJ_________"
				"HJQJQEJ_________DHGHQG__________"
				"FQJQWEQHQJHJGH__QWEWETW_________"
				"GGQJQEE_________HJQJQWQGGREWQE__"
				"EYTEWQQWQWTE____EYTEWQQWQWJH____"
				"HJQJQEJ_________DHGHQG__________"
				"FDFDFQD_________QQJFFJJ_________"
				"HJQJQEJ_________DHGHQG__________"
				"DFQJQWEQH_______QJHJGH__________";

int read_once(string _ini_path = ini_path) {
	LPWSTR ini_path = stringToLPWSTR(_ini_path);
	LPWSTR _score = new WCHAR[max_length];
	LPWSTR _BPM = new WCHAR[max_length];
	LPWSTR _INR = new WCHAR[max_length];
	LPWSTR _KeyUpDelay = new WCHAR[max_length];
	GetPrivateProfileStringW(L"CONFIG", L"score", L"NULL", _score, max_length, ini_path);
	GetPrivateProfileStringW(L"CONFIG", L"BPM", L"NULL", _BPM, max_length, ini_path);
	GetPrivateProfileStringW(L"CONFIG", L"INR", L"NULL", _INR, max_length, ini_path);
	GetPrivateProfileStringW(L"CONFIG", L"KeyUpDelay", L"NULL", _KeyUpDelay, max_length, ini_path);
	score = WCharToMByte(_score);
	BPM = stof(WCharToMByte(_BPM));
	INR = stof(WCharToMByte(_INR));
	KeyUpDelay = stof(WCharToMByte(_KeyUpDelay));
}

int main()
{
	if (isFileExists_stat(ini_path) == false) {
		cout << "未找到配置，尝试创建..." << endl;
		create_ini_file();
		write_ini_entry("CONFIG", "score", score);
		write_ini_entry("CONFIG", "BPM", std::to_string(BPM));
		write_ini_entry("CONFIG", "INR", std::to_string(INR));
		write_ini_entry("CONFIG", "KeyUpDelay", std::to_string(KeyUpDelay));
	}
	else {
		cout << "尝试读取配置..."<< endl;
		try {
			read_once();
		}
		catch (...) {
			cout << "检查配置文件，位于当前目录的config.ini" << endl;
			return 0;
		}
	}
	while (true) {
		cout << "1、创建配置" << endl;
		cout << "2、播放按键" << endl;
		cin >> option;
		if (!(1 <= option <= 2)) {
			cout << "当前配置选项为：" << option << endl;
			cout << "输入正确选项" << endl;
		}
		else {
			switch (option)
			{
			case 1: {
				create_ini_file();
				write_ini_entry("CONFIG", "score", score);
				write_ini_entry("CONFIG", "BPM", std::to_string(BPM));
				write_ini_entry("CONFIG", "INR", std::to_string(INR));
				write_ini_entry("CONFIG", "KeyUpDelay", std::to_string(KeyUpDelay));
				break;
			}
			case 2: {
				char *p = &score[0];
				system("pause");
				Sleep(1000 * 5);
				for (int i = 0; i < score.length(); i++) {
					cout << *p << endl;
					if (*p != '_') {
						Sleep(1000 * INR);
						keybd_event(*p, 0, 0, 0);
						Sleep(KeyUpDelay);
						keybd_event(*p, 0, KEYEVENTF_KEYUP, 0);
					}
					else if (*p == '_') {
						Sleep(1000 * INR);
					}
					p = p + 1;
				}
				cout << "播放完成..." << endl;
				break;
			}
			default:
				cout << "~" << endl;
			}
		}
	}
}