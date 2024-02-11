#include "SMS_Sender.h"

namespace Notofication {

    bool SmsSender::TryParseAsJson(string& response, nlohmann::ordered_json& ObjResponse)
    {
        try
        {
            ObjResponse = ordered_json::parse(response);
            return true;
        }
        catch (json::exception	 e)
        {
            return false;
        }

    }//TryParseAsJson

    void SmsSender::replaceAll(string& str, const string& from, const string& to) {
        if (from.empty())
            return;
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        }
    }//replaceAll

    void SmsSender::url_encode(string& str) 
    {
        std::ostringstream encodedStream;
        encodedStream << std::hex << std::uppercase << std::setfill('0');

        for (char c : str) {
            if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
                encodedStream << c;
            }
            else {
                encodedStream << '%' << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(c));
            }
        }

        str = encodedStream.str();
        
    }//url_encode

  

}//namespace Notofication

