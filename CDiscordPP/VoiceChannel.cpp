#include "CDiscordPP.h"

using namespace CDiscordPP;

VoiceChannel::VoiceChannel(ID _id, Guild *_parent) : Entity(_id, _parent)
{
	//
}

CDiscordPP::VoiceChannel::~VoiceChannel()
{
	//
}

String CDiscordPP::VoiceChannel::GetName()
{
	return String();
}

Array<User*> CDiscordPP::VoiceChannel::GetUsers()
{
	return Array<User*>();
}

unsigned int CDiscordPP::VoiceChannel::GetSamplerate()
{
	return 0;
}

unsigned int CDiscordPP::VoiceChannel::GetBitrate()
{
	//OpusEncoder *encoder = opus_encoder_create();
	return 0;
}

#ifdef CDISCORDPP_AUDIO
void CDiscordPP::VoiceChannel::SetAudioInput(bool enable)
{
	//
}
#endif