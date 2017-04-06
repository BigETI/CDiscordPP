#include "CDiscordPP.h"

using namespace CDiscordPP;

Guild::Guild(ID _id, Connector *_parent) : Entity(_id, _parent)
{
	//
}

Array<Channel*> CDiscordPP::Guild::GetChannels()
{
	return Array<Channel*>();
}

Channel * CDiscordPP::Guild::GetChannelByID(ID channel_id)
{
	return nullptr;
}

Array<Role*> CDiscordPP::Guild::GetRoles()
{
	return Array<Role*>();
}

Role * CDiscordPP::Guild::GetRoleByID(ID role_id)
{
	return nullptr;
}

Array<User*> CDiscordPP::Guild::GetUsers()
{
	return Array<User*>();
}

User * CDiscordPP::Guild::GetUserByID(ID user_id)
{
	return nullptr;
}

Array<VoiceChannel*> CDiscordPP::Guild::GetVoiceChannels()
{
	return Array<VoiceChannel*>();
}

VoiceChannel * CDiscordPP::Guild::GetVoiceChannelByID(ID voice_channel_id)
{
	return nullptr;
}

Channel * CDiscordPP::Guild::CreateChannel(String channel_name)
{
	return nullptr;
}
