#include "HTTPClientV2.hpp"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void HTTPClient::replaceAll(string& str, const string& from, const string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}



void HTTPClient::MAKE_REQUEST(HTTPRequest& HR)
{
	HR.response = "";//empty the current value of reference;

	replaceAll(HR.parameters, "#", "%23");
	replaceAll(HR.parameters, "+", "%2B");

	CURL* curl;
	CURLcode res;

	curl = curl_easy_init();

	if (HR.URL.empty() || (!curl))
	{
		HR.response = "CURL_FAILED";
		curl_easy_cleanup(curl);
		return;
	}

	curl_global_init(CURL_GLOBAL_ALL);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.38.0");

	if (HR.request_type == HttpRequestType::POST)
	{
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, HR.parameters.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, HR.parameters.length());
	}
	else if (HR.request_type == HttpRequestType::GET)
	{
		curl_easy_setopt(curl, CURLOPT_POST, 0); 
		replaceAll(HR.URL, "#", "%23");
		replaceAll(HR.URL, "+", "%2B");
	}
	else
	{
		HR.response = "CURL_FAILED";
		curl_easy_cleanup(curl);
		return;
	}

	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //debug

	if (!HR.secure)
	{
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);  // for --insecure option
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
	}

	if (HR.headers.size() > 0)
	{
		struct curl_slist* headers = NULL;

		for (auto header : HR.headers)
		{
			headers = curl_slist_append(headers, header.c_str());
		}
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	}

	curl_easy_setopt(curl, CURLOPT_URL, HR.URL.c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &HR.response);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
	res = curl_easy_perform(curl);

	if (res != 0)
	{
		HR.response = "CURL_FAILED";
		curl_easy_cleanup(curl);
		return;
	}

	curl_easy_cleanup(curl);

}//MAKE_REQUEST


