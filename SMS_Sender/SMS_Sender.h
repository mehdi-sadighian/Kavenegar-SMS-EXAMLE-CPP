#pragma once

#ifndef SMS_Sender_H
#define SMS_Sender_H

#include <cstdio>
#include <unistd.h>
#include <string>
#include <iostream>
#include <thread>
#include <sys/time.h>
#include <vector>
#include <cctype>
#include <iomanip>
#include <sstream>

#include "../HTTPClient/HTTPClientV2.hpp"
#include "../json/json.hpp"

using namespace std;
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;


namespace Notofication {

	typedef vector <string> RecieversPhoneNumber;
	typedef vector <string> RecieversEmail;


	struct KaveNegarSetting
	{
		string Api_Base_Url;
		string SendSmsRoute;
		string SendOtpSmsRoute;
		string API_KEY;
	};


	class SmsSender
	{
	public:
		
		virtual bool SendSms(string& message, string& sender_number, RecieversPhoneNumber& RPN, string& error) = 0;
		virtual bool SendOTPSms(string& PhoneNumber, string& token, string& templateName, string& error) = 0;

		SmsSender() {}
		~SmsSender() {}
		

	private:

	protected:
		HTTPClient Http_Client;
		
		void url_encode(string& str);
		void replaceAll(string& str, const string& from, const string& to);
		bool TryParseAsJson(string& response, nlohmann::ordered_json& ObjResponse);
		
	};

	
	class KaveNegar:public SmsSender
	{
	public:


		KaveNegar(KaveNegarSetting& KaveNegarSetting) 
		{
			this->SendSmsUrl = KaveNegarSetting.Api_Base_Url + KaveNegarSetting.API_KEY + KaveNegarSetting.SendSmsRoute;
			this->SendOtpSmsUrl = KaveNegarSetting.Api_Base_Url + KaveNegarSetting.API_KEY + KaveNegarSetting.SendOtpSmsRoute;
		}

		~KaveNegar() {}

		bool SendSms(string& message, string& sender_number, RecieversPhoneNumber& RPN, string& error);
		bool SendOTPSms(string& PhoneNumber, string& token, string& templateName, string& error);
		
	private:

		string SendSmsUrl, SendOtpSmsUrl;
	
	};

	

}//namespace Notofication

#endif // !SMS_Sender_H


