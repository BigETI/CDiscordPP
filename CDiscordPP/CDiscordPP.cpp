#include "CDiscordPP.h"

using namespace CDiscordPP;

void CDiscordPP::BeginSession(String bot_token)
{
	try
	{
		Connector connector(bot_token);
		/*Array<Guild *> guilds(connector.GetConnectedGuilds());
		for (Array<Guild *>::iterator it = guilds.begin(), end = guilds.end(); it != end; ++it)
		{

		}*/
	}
	catch (...)
	{
		//
	}
}

Thread *CDiscordPP::BeginSessionThread(String bot_token)
{
	return nullptr;
}
