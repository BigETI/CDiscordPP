#include "CDiscordPP.h"
#include <curl/curl.h>
#include <codecvt>

using namespace CDiscordPP;

JSON send_http_request(Connector *connector, JSON json, String endpoint)
{
	JSON ret;
	Connector::InitCURL();
	CURL *curl = curl_easy_init();
	if (curl)
	{
		ANSIString url = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(connector->GetHTTPURL(endpoint));
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		CURLcode res(curl_easy_perform(curl));
		if (res == CURLE_OK)
		{
			
		}
		curl_easy_cleanup(curl);
	}
	return ret;
}

bool Connector::curl_ni(true);

const String Connector::base_http_url(L"https://discordapp.com/api");

Connector::Connector(String _bot_token) : bot_token(_bot_token), shards()
{
	UpdateGateway();
}

CDiscordPP::Connector::~Connector()
{
	CleanUp();
}

void CDiscordPP::Connector::InitCURL()
{
	if (curl_ni)
	{
		curl_ni = false;
		curl_global_init(CURL_GLOBAL_DEFAULT);
	}
}

void CDiscordPP::Connector::CleanUp()
{
	if (!curl_ni)
	{
		curl_ni = true;
		curl_global_cleanup();
	}
}

void CDiscordPP::Connector::UpdateGateway(bool force)
{
	/*if (force || gateway_url.empty())
	{
		JSON result(SendHTTPRequest({}, L"Authorization: Bot " + bot_token, L"/gateway/bot").get());
		gateway_url = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(result[L"url"].get<ANSIString>());
		unsigned int shard_count = result[L"shards"];
		if (shards.size() != shard_count)
			shards.resize(shard_count);
	}*/
}

String CDiscordPP::Connector::GetBotToken()
{
	return bot_token;
}

Array<Guild*> CDiscordPP::Connector::GetConnectedGuilds()
{
	return std::vector<Guild*>();
}

Guild * CDiscordPP::Connector::GetGuildByID(ID id)
{
	Guild *ret(nullptr);

	return ret;
}

String CDiscordPP::Connector::GetHTTPURL(String endpoint)
{
	return base_http_url + endpoint;
}

Future<JSON> CDiscordPP::Connector::SendRequest(const JSON & json, String endpoint)
{
	return Future<JSON>();
}

Future<JSON> CDiscordPP::Connector::SendHTTPRequest(const JSON & json, String header, String endpoint)
{
	return std::async(send_http_request, this, json, endpoint);
}
