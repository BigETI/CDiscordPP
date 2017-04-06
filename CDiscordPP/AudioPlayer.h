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

		AudioPlayer(const AudioPlayer &);
		AudioPlayer & operator = (const AudioPlayer &);

	public:
		AudioPlayer();
		AudioPlayer(String device_name);
		static Array<String> GetDeviceNames();
		void UpdateContext();
		void SetDevice(String device_name);
		void Play();
		void Pause();
	};
}

#endif
