#include "CDiscordPP.h"

using namespace CDiscordPP;

Message::Message(ID _id, Channel *_parent) : Entity(_id, _parent)
{
	//
}

CDiscordPP::Message::~Message()
{
	//
}

String CDiscordPP::Message::GetContent()
{
	return String();
}

User * CDiscordPP::Message::GetAuthor()
{
	return nullptr;
}

void CDiscordPP::Message::EditMessage(String message)
{
	//
}
