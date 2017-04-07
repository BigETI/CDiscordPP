#ifndef __CDISCORDPP_AUDIOSTREAM_H__
#	define __CDISCORDPP_AUDIOSTREAM_H__

namespace CDiscordPP
{
	class AudioStream
	{
	private:
		SharedPointer<InputStream> stream;
		Mutex mtx;

		AudioStream();
		AudioStream(const AudioStream &);
		AudioStream & operator = (const AudioStream &);

	public:
		AudioStream(SharedPointer<InputStream> _stream);
		~AudioStream();
		void LockThread();
		void UnlockThread();
		Array<int8_t> & GetData(Array<int8_t> & data, size_t request_len);
	};
}

#endif