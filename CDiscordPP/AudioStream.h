#ifndef __CDISCORDPP_AUDIOSTREAM_H__
#	define __CDISCORDPP_AUDIOSTREAM_H__

namespace CDiscordPP
{
	class AudioStream
	{
	private:
		Array<int8_t> data;

		AudioStream();
		AudioStream(const AudioStream &);
		AudioStream & operator = (const AudioStream &);

	public:
		AudioStream(InputStream & stream);
		
	};
}

#endif