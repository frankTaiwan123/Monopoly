#pragma once
#include<string>
class Event
{
public:
	Event();
	~Event();

	static void getEvent();

	static int eventCode;
	static std::wstring eventNames[10];
};

