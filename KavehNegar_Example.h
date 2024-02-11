#pragma once

#include "Libs/SMS_Sender/SMS_Sender.h"

void KavehNegarExample()
{
    Notofication::KaveNegarSetting KaveNegarSetting;


    KaveNegarSetting.Api_Base_Url = "https://api.kavenegar.com/v1/";
    KaveNegarSetting.SendSmsRoute = "/sms/send.json";
    KaveNegarSetting.SendOtpSmsRoute = "/verify/lookup.json";
    KaveNegarSetting.API_KEY = "644751304D5155772B626847312B637A4862343438472B766C6762456841316C7A7A656F6B7757432B61633D";
    
    Notofication::KaveNegar KaveNegar(KaveNegarSetting);

    string number = "09126417351";
    string token = "4242";
    string template_name = "BarghetoOTP";
    string error;

    if (!KaveNegar.SendOTPSms(number, token, template_name, error))
        cout << error << endl;

    string message = "test";
    string sender_number = "10008001002000";

    Notofication::RecieversPhoneNumber RPN;
    RPN.push_back(number);

    if (!KaveNegar.SendSms(message, sender_number, RPN, error))
        cout << error << endl;

  
}//KavehNegarExample