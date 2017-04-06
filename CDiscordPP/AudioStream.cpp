#include "CDiscordPP.h"

CDiscordPP::AudioStream::AudioStream(InputStream & stream)
{
	int r = -1;
	while ((r = stream.get()) != -1)
		data.push_back(r);
}
