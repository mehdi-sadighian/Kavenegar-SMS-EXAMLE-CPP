#include "SMS_Sender.h"


namespace Notofication {

	bool KaveNegar::SendSms(string& message,string& sender_number, RecieversPhoneNumber& RPN,string& error)
	{
		if (RPN.size() <= 0)
		{
			error = "No Phone Number In List";
			return false;
		}

		HTTPRequest HR;
		HR.request_type = HttpRequestType::POST;

		HR.URL = SendSmsUrl;
		HR.URL += "?receptor=";

		for (int i = 0; i < RPN.size(); i++)
		{
			HR.URL += RPN[i];
			HR.URL += ",";
		}

		HR.URL.pop_back();//remove last ","

		HR.URL += "&sender=" + sender_number + "&message=";

		url_encode(message);

		HR.URL += message;
		
		HR.parameters = "";
		HR.headers = {};

		Http_Client.MAKE_REQUEST(HR);

		nlohmann::ordered_json ObjResponse;

		if (!TryParseAsJson(HR.response, ObjResponse))
		{
			error = "Failed To Parse Response:" + HR.response;
			return false;
		}

		int code;

		try
		{
			code = ObjResponse["return"]["status"];
		}
		catch (exception e)
		{
			error = "Failed To Read Json:" + HR.response;
			return false;
		}

		if (code != 200)
		{
			error = "Not Success:" + HR.response;
			return false;
		}
			
		return true;
	}//SendSms

	bool KaveNegar::SendOTPSms(string& PhoneNumber, string& token, string& templateName, string& error)
	{
		HTTPRequest HR;
		HR.request_type = HttpRequestType::GET;

		HR.URL = SendOtpSmsUrl;
		HR.URL += "?receptor=";
		HR.URL += PhoneNumber;
		HR.URL += "&token=" + token + "&template=" + templateName;

		HR.parameters = "";
		HR.headers = {};

		Http_Client.MAKE_REQUEST(HR);

		nlohmann::ordered_json ObjResponse;

		if (!TryParseAsJson(HR.response, ObjResponse))
		{
			error = "Failed To Parse Response:" + HR.response;
			return false;
		}

		int code;

		try
		{
			code = ObjResponse["return"]["status"];
		}
		catch (exception e)
		{
			error = "Failed To Read Json:" + HR.response;
			return false;
		}

		if (code != 200)
		{
			error = "Not Success:" + HR.response;
			return false;
		}

		return true;
	}//SendOTPSms


}//namespace Notofication
