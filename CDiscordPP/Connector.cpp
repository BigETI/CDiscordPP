#include "CDiscordPP.h"
#include <curl/curl.h>
#include <codecvt>

/*#	if defined WIN32 || defined _WIN32 || defined __WIN32_
#		include <windows.h>
#		include <winsock2.h>
#		include <ws2tcpip.h>
#		define close closesocket
#	else
#		include <sys/types.h>         
#		include <sys/socket.h>        
#		include <netinet/in.h>
#		include <arpa/inet.h>         
#		include <unistd.h>            
#	endif*/

//#include <websocketpp/client.hpp>

using namespace CDiscordPP;

static WSADATA wsa_data;

/*typedef enum {
	CURLSOCKTYPE_IPCXN,
	CURLSOCKTYPE_ACCEPT,
	CURLSOCKTYPE_LAST
} curlsocktype;

struct curl_sockaddr {
	int family;
	int socktype;
	int protocol;
	unsigned int addrlen;
	struct sockaddr addr;
};*/

static curl_socket_t opensocket_callback(void *clientp, curlsocktype purpose, struct curl_sockaddr *address)
{
	curl_socket_t ret;
	return ret;
}

static size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata)
{
	return size;
}

static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t ret = size * nmemb;
	static_cast<ANSIString *>(userdata)->append(static_cast<char *>(ptr), ret);
	return ret;
}

// TO-DO
static void gateway_thread(Connector *connector)
{
	//CURLcode res;
	struct sockaddr_in servaddr;
	Connector::InitNetworking();
	struct curl_slist *headers = nullptr;
	CURL *curl = curl_easy_init();
	if (curl)
	{
		headers = curl_slist_append(headers, "HTTP/1.1 101 WebSocket Protocol Handshake");
		headers = curl_slist_append(headers, "Upgrade: WebSocket");
		headers = curl_slist_append(headers, "Connection: Upgrade");
		//headers = curl_slist_append(headers, "Sec-WebSocket-Version: 13");
		//headers = curl_slist_append(headers, "Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==");
		ANSIString gateway_url = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(connector->GetGatewayURL());
		curl_easy_setopt(curl, CURLOPT_URL, gateway_url.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_OPENSOCKETFUNCTION, opensocket_callback);
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		//curl_easy_setopt(curl, CURLOPT_URL, "https://&#8217");
		curl_socket_t sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd != CURL_SOCKET_BAD)
		{
			memset(&servaddr, 0, sizeof(servaddr));
			servaddr.sin_family = AF_INET;
			servaddr.sin_port = 80U;
		}
		curl_easy_cleanup(curl);
	}
}

static size_t write_http_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t ret = size * nmemb;
	static_cast<ANSIString *>(userdata)->append(static_cast<char *>(ptr), ret);
	return ret;
}

static JSON send_request(Connector *connector, JSON & json)
{
	JSON ret;
	return ret;
}

static JSON send_http_request(Connector *connector, JSON & json, String endpoint, Array<String> *headers)
{
	JSON ret;
	Connector::InitNetworking();
	CURL *curl = curl_easy_init();
	if (curl)
	{
		ANSIString url = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(connector->GetHTTPURL(endpoint));
		ANSIString response;
		struct curl_slist *hs = nullptr;
		std::ostringstream oss;
		std::cout << "Performing send_http_request:\n\tURL:\t" << url << "\n\tHeaders:";
		if (headers)
		{
			for (Array<String>::iterator it = headers->begin(), end = headers->end(); it != end; ++it)
			{
				ANSIString s(std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(*it));
				std::cout << "\n\t\t" << s;
				hs = curl_slist_append(hs, s.c_str());
			}
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
		}
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_http_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		CURLcode res(curl_easy_perform(curl));
		if (res == CURLE_OK)
		{
			std::cout << "\n\nsend_http_request successful!\n\tResponse:\t" << response;
			ret = JSON::parse(response.c_str());
		}
		else
		{
			std::cout << "\n\nsend_http_request failed!\n\tResponse:\t" << response;
		}
		curl_slist_free_all(hs);
		curl_easy_cleanup(curl);
	}
	return ret;
}

bool Connector::curl_ni(true);
String Connector::gateway_url;

const String Connector::base_http_url(L"https://discordapp.com/api");
//const String Connector::base_http_url(L"http://bigeti.de/test/discord.php");

Connector::Connector(String _bot_token) : bot_token(_bot_token), shards()
{
	UpdateGateway();
	OpenGateway();
}

CDiscordPP::Connector::~Connector()
{
	CleanUp();
}

void CDiscordPP::Connector::InitNetworking()
{
	if (curl_ni)
	{
		curl_ni = false;
		curl_global_init(CURL_GLOBAL_DEFAULT);
#ifdef WIN32
		int initwsa = WSAStartup(MAKEWORD(2, 0), &wsa_data);
		if (initwsa != 0) {
			CleanUp();
		}
#endif
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
	if (force || gateway_url.empty())
	{
		Array<String> headers;
		headers.push_back(L"Authorization: Bot " + bot_token);
		headers.push_back(L"User-Agent: DiscordBot (https://github.com/BigETI/CDiscordPP, 0.0.0.0) - CDiscordPP CDiscordPP is a C++ library for the Discord API");
		headers.push_back(L"Content-Type: application/json");
		JSON result(SendHTTPRequest({}, L"/gateway/bot", &headers).get());
		// Unauthorized
		//{"code": 0, "message": "401: Unauthorized"}
		// Authorized
		//{"url": "wss://gateway.discord.gg", "shards": 1}
		gateway_url = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(result.at("url").get<ANSIString>());
		unsigned int shard_count = result.at("shards");
		if (shards.size() != shard_count)
			shards.resize(shard_count);
	}
}

void CDiscordPP::Connector::OpenGateway()
{
	//
}

void CDiscordPP::Connector::CloseGateway()
{
	//
}

String CDiscordPP::Connector::GetGatewayURL()
{
	return gateway_url;
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

Future<JSON> CDiscordPP::Connector::SendRequest(const JSON & json)
{
	InitNetworking();
	return Future<JSON>();
}

Future<JSON> CDiscordPP::Connector::SendHTTPRequest(const JSON & json, String endpoint, Array<String> *headers)
{
	InitNetworking();
	return std::async(send_http_request, this, json, endpoint, headers);
}
