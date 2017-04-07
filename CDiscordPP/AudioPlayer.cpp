#include "CDiscordPP.h"
#include <opus.h>
#include <codecvt>

using namespace CDiscordPP;

void audio_queue_player(AudioPlayer *player)
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
	while (player->IsPlaying())
	{

	}
}

CDiscordPP::AudioPlayer::AudioPlayer() : context(nullptr), device(nullptr), is_playing(false)
{
	device = alcOpenDevice(nullptr);
	UpdateContext();
}

AudioPlayer::AudioPlayer(String device) : context(nullptr), device(nullptr), is_playing(false)
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

void CDiscordPP::AudioPlayer::AddStreamToQueue(SharedPointer<InputStream> stream)
{
	mtx.lock();
	try
	{
		audio_queue.push(new AudioStream(stream));
	}
	catch (...)
	{
		//
	}
	mtx.unlock();
}

void CDiscordPP::AudioPlayer::AddFileToQueue(String file_name)
{
	try
	{
		SharedPointer<InputStream> is(new InputFileStream(file_name, std::ios::in));
		if (is)
			AddStreamToQueue(is);
	}
	catch (...)
	{
		//
	}
	
}

void CDiscordPP::AudioPlayer::Play()
{
	is_playing = true;
	std::async(audio_queue_player, this);
}

void CDiscordPP::AudioPlayer::Stop()
{
	is_playing = true;
}

bool CDiscordPP::AudioPlayer::IsPlaying()
{
	return is_playing;
}
