#ifndef __CDISCORDPP_VOICECHANNEL_H__
#	define __CDISCORDPP_VOICECHANNEL_H_

namespace CDiscordPP
{
	class VoiceChannel : public Entity<Guild>
	{
	private:
		String name;

		VoiceChannel();
		VoiceChannel(const VoiceChannel &);
		VoiceChannel & operator = (const VoiceChannel &);

	CDISCORDPP_PACKAGE:
		VoiceChannel(ID _id, Guild *_parent);
		~VoiceChannel();

	public:
		String GetName();
		Array<User *> GetUsers();
		unsigned int GetSamplerate();
		unsigned int GetBitrate();
#	ifdef CDISCORDPP_AUDIO
		void SetAudioInput(bool enable);
#	endif


	};
}

#endif