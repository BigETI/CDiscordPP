#ifndef __CDISCORDPP_H__
#	define __CDISCORDPP_H__

#	include <fstream>
#	include <string>
#	include <cstdint>
#	include <vector>
//#	include <thread>
#	include <future>
#	include <ctpl_stl.h>
#	include <json.hpp>

#	define EXTERN_C	extern "C"
#	if defined __CYGWIN__ || WIN32 || defined _WIN32 || defined __WIN32_
#		ifdef __GNUC__
#			define CDISCORDPP_DLL_EXPORT	__attribute__ ((dllexport))
#			define CDISCORDPP_DLL_IMPORT	__attribute__ ((dllimport))
#		else
#			define CDISCORDPP_DLL_EXPORT	__declspec(dllexport)
#			define CDISCORDPP_DLL_IMPORT	__declspec(dllimport)
#		endif
#	else
#		define	CDISCORDPP_DLL_EXPORT
#		define	CDISCORDPP_DLL_IMPORT
#	endif

#	ifdef CDISCORDPP_LIB
#		define CDISCORDPP_PACKAGE	public
#	else
#		define CDISCORDPP_PACKAGE	private
#	endif

namespace CDiscordPP
{
	using ID = uint64_t;
	using JSON = nlohmann::json;
	using String = std::wstring;
	using ANSIString = std::string;
	//using Thread = std::thread;
	template < class _T > using Future = std::future<typename _T>;
	template < class _T > using Array = std::vector<typename _T>;
	template < class _T > using Queue = std::queue<typename _T>;
	using InputStream = std::istream;
	using InputFileStream = std::ifstream;
	using Mutex = std::mutex;

	template < class _T > class Entity;
	class Connector;
	class Guild;
	class Channel;
	class Message;
	class Role;
	class User;
	class VoiceChannel;
#	ifdef CDISCORDPP_AUDIO
	class AudioPlayer;
	class AudioStream;
#	endif
}

#	include "./Entity.h"
#	include "./Channel.h"
#	include "./Connector.h"
#	include "./Guild.h"
#	include "./Message.h"
#	include "./Role.h"
#	include "./User.h"
#	include "./VoiceChannel.h"
#	ifdef CDISCORDPP_AUDIO
#		include "./AudioPlayer.h"
#		include "./AudioStream.h"
#	endif

EXTERN_C namespace CDiscordPP
{
	static Connector *Instantiate(String api_key);
	CDISCORDPP_DLL_IMPORT void OnStart();
	CDISCORDPP_DLL_IMPORT void OnChatMessage(String message_id);
}

#endif
