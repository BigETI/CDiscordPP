#include "CDiscordPP.h"
#include <opus.h>
#include <codecvt>

using namespace CDiscordPP;

CDiscordPP::AudioPlayer::AudioPlayer() : context(nullptr), device(nullptr)
{
	device = alcOpenDevice(nullptr);
	UpdateContext();
}

AudioPlayer::AudioPlayer(String device) : context(nullptr), device(nullptr)
{
	SetDevice(device);
}

Array<String> CDiscordPP::AudioPlayer::GetDeviceNames()
{
	Array<String> ret;
	const ALCchar *device(alcGetString(NULL, ALC_DEVICE_SPECIFIER)), *next(device + 1);
	size_t len(0);
	while (device && ((*device) != '\0') && next && ((*next) != '\0'))
	{
		ret.push_back(std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(device).c_str());
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
	return ret;
}

void CDiscordPP::AudioPlayer::UpdateContext()
{
	if (context)
	{
		alcDestroyContext(context);
		context = nullptr;
	}
	if (device)
		context = alcCreateContext(device, nullptr);
}

void CDiscordPP::AudioPlayer::SetDevice(String device_name)
{
	if (context)
	{
		alcDestroyContext(context);
		context = nullptr;
	}
	if (device)
	{
		alcCloseDevice(device);
		device = nullptr;
	}
	device = alcOpenDevice(std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(device_name).c_str());
	UpdateContext();
}

void CDiscordPP::AudioPlayer::Play()
{
	ALuint source;
	alGenSources(1, &source);
	alSourcef(source, AL_PITCH, 1.0f);
	alSourcef(source, AL_GAIN, 1.0f);
	alSource3f(source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alSourcei(source, AL_LOOPING, AL_FALSE);
	ALuint buffer;
	alGenBuffers(1, &buffer);
	alSourcePlay(source);
}

void CDiscordPP::AudioPlayer::Pause()
{
	//
}
