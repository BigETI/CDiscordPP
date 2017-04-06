#ifndef __CDISCORDPP_CHANNEL_H__
#	define __CDISCORDPP_CHANNEL_H__

namespace CDiscordPP
{
	class Channel : public Entity<Guild>
	{
	private:
		Channel();
		Channel(const Channel &);
		Channel & operator = (const Channel &);

	CDISCORDPP_PACKAGE:
		Channel(ID _id, Guild *_parent);
		~Channel();
		Message *GetMessageObject(const JSON & json);

	public:
		Future<Message *>WriteMessage(String message, bool tts, bool embed);
		Future<Array<Message *>> GetMessages();
		Future<Message *>GetMessageByID(ID message_id);
	};
}

#endif