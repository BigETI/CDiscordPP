#ifndef __CDISCORDPP_MESSAGE_H__
#	define __CDISCORDPP_MESSAGE_H__

namespace CDiscordPP
{
	class Message : public Entity<Channel>
	{
	private:
		String content;
		Message();
		Message(const Message &);
		Message & operator = (const Message &);

	CDISCORDPP_PACKAGE:
		Message(ID _id, Channel *_parent);
		~Message();

	public:
		String GetContent();
		User *GetAuthor();
		void EditMessage(String message);
	};
}

#endif