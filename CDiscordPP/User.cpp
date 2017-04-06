#include "CDiscordPP.h"

using namespace CDiscordPP;

User::User(ID _id, Connector *_parent) : Entity(_id, _parent)
{
	//
}

CDiscordPP::User::~User()
{
}

String CDiscordPP::User::GetName()
{
	return String();
}
