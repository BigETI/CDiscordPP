#include "CDiscordPP.h"

using namespace CDiscordPP;

AudioStream::AudioStream(SharedPointer<InputStream> _stream) : stream(_stream)
{
	//
}

CDiscordPP::AudioStream::~AudioStream()
{
	//
}

void AudioStream::LockThread()
{
	mtx.lock();
}

void AudioStream::UnlockThread()
{
	mtx.unlock();
}

Array<int8_t> & AudioStream::GetData(Array<int8_t> & data, size_t request_len)
{
	int d;
	data.clear();
	data.reserve(request_len);
	for (size_t i = 0UL; i != request_len; i++)
	{
		d = stream.get()->get();
		if (d == -1)
			break;
		else
			data.push_back(d);
	}
	return data;
}
