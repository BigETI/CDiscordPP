#ifndef __CDISCORDPP_GUILD_H__
#	define __CDISCORDPP_GUILD_H__

namespace CDiscordPP
{
	class Guild : public Entity<Connector>
	{
	private:
		Guild();
		Guild(const Guild &);
		Guild & operator = (const Guild &);
	CDISCORDPP_PACKAGE:
		Guild(ID _id, Connector *_parent);
	public:
		Array<Channel *> GetChannels();
		Channel *GetChannelByID(ID channel_id);
		Array<Role *> GetRoles();
		Role *GetRoleByID(ID role_id);
		Array<User *> GetUsers();
		User *GetUserByID(ID user_id);
		Array<VoiceChannel *> GetVoiceChannels();
		VoiceChannel *GetVoiceChannelByID(ID voice_channel_id);

		Channel *CreateChannel(String channel_name);
	};
}
#endif