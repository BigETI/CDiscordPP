#ifndef __CDISCORDPP_AUDIOPLAYER_H__
#	define __CDISCORDPP_AUDIOPLAYER_H__

#	include <al.h>
#	include <alc.h>

namespace CDiscordPP
{
	class AudioPlayer
	{
	private:
		ALCcontext *context;
		ALCdevice *device;
		Queue<AudioStream *> audio_queue;
		std::mutex mtx;
		bool is_playing;

		AudioPlayer(const AudioPlayer &);
		AudioPlayer & operator = (const AudioPlayer &);

	public:
		AudioPlayer();
		AudioPlayer(String device_name);
		static Array<String> GetDeviceNames();
		void UpdateContext();
		void SetDevice(String device_name);
		void AddStreamToQueue(SharedPointer<InputStream> stream);
		void AddFileToQueue(String file_name);
		void Play();
		void Stop();
		bool IsPlaying();
	};
}

#endif
