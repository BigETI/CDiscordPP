#include "CDiscordPP.h"

using namespace CDiscordPP;

Role::Role(ID _id, Guild *_parent) : Entity(_id, _parent)
{
	//
}

CDiscordPP::Role::~Role()
{
	//
}

String CDiscordPP::Role::GetName()
{
	return String();
}
