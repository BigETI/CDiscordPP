#include "CDiscordPP.h"

using namespace CDiscordPP;

Message *write_message(Channel *channel, String message, bool tts, bool embed)
{
	//std::future<JSON> r(channel->GetParent()->GetParent()->SendRequest({ { L"content", message },{ "tts", tts },{ L"embed", embed } }, L"/channels/" + std::to_wstring(channel->GetID()) + L"/messages"));
	//JSON result = r.get();
	//return channel->GetMessageObject(result);
	return nullptr;
}

Array<Message *> get_messages(Channel *channel)
{
	Array<Message *> ret;
	return ret;
}

Message *get_message_by_id(Channel *channel, ID message_id)
{
	Message *ret(nullptr);
	return ret;
}

Channel::Channel(ID _id, Guild *_parent) : Entity(_id, _parent)
{
	//
}

Channel::~Channel()
{
	//
}

Message *Channel::GetMessageObject(const JSON & json)
{
	Message *ret = nullptr;
	if (json.is_object())
	{
		if (json.at("id").is_string() && json.at("channel_id").is_string())
		{
			ANSIString t = json.at("channel_id");
			ID channel_id(stoll(t));
			if (channel_id == GetID())
			{
				t = json.at("id").get<ANSIString>();
				try
				{
					ret = new Message(stoll(t), this);
				}
				catch (...)
				{
					//
				}
			}
		}
	}
	return ret;
}

std::future<Message *> CDiscordPP::Channel::WriteMessage(String message, bool tts, bool embed)
{
	return std::async(write_message, this, message, tts, embed);
}

std::future<Array<Message *>> CDiscordPP::Channel::GetMessages()
{
	return std::async(get_messages, this);
}

std::future<Message *> CDiscordPP::Channel::GetMessageByID(ID message_id)
{
	return std::async(get_message_by_id, this, message_id);
}

