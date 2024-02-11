#pragma once

#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H



#include <cstdio>
#include <unistd.h>
#include <string>
#include <iostream>
#include <curl/curl.h>
#include <set>
#include <functional>

using namespace std;

	enum class HttpRequestType
	{
		GET = 1,
		POST = 2
	};

	struct HTTPRequest
	{
		string URL;
		string parameters;
		set<string> headers;
		bool secure;
		HttpRequestType request_type;
		string response;
	};

	size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

	class HTTPClient
	{
		public:
		void MAKE_REQUEST(HTTPRequest& HR);
		//string CURL_MAKE_REQUEST2(string URL, string parameters, set<string>& headerstring, bool secure, string request_type);

		private:
		void replaceAll(string& str, const string& from, const string& to);

	};




#endif