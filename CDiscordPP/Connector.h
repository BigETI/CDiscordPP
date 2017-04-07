#ifndef __CDISCORDPP_CONNECTOR_H__
#	define __CDISCORDPP_CONNECTOR_H__

namespace CDiscordPP
{
	class Connector
	{
	private:
		static bool curl_ni;
		static const String base_http_url;
		static String gateway_url;
		ctpl::thread_pool shards;
		String bot_token;
		//curl_socket_t sockfd;
		Queue<JSON> request_pool;

		Connector();
		Connector(const Connector &);
		Connector & operator = (const Connector &);

	CDISCORDPP_PACKAGE:
		Connector(String _bot_token);
		~Connector();
		static void InitNetworking();
		static void CleanUp();
		void UpdateGateway(bool force = false);
		void OpenGateway();
		void CloseGateway();

	public:
		static String GetGatewayURL();
		String GetBotToken();
		Array<Guild *> GetConnectedGuilds();
		Guild *GetGuildByID(ID id);
		String GetHTTPURL(String endpoint);
		std::future<JSON> SendRequest(const JSON & json);
		std::future<JSON> SendHTTPRequest(const JSON & json, String endpoint, Array<String> *headers = nullptr);
	};
}

#endif