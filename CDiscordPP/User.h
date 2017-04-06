#ifndef __CDISCORDPP_USER_H__
#	define __CDISCORDPP_USER_H__

namespace CDiscordPP
{
	class User : Entity<Connector>
	{
	private:
		User();
		User(const User &);
		User & operator = (const User &);

	CDISCORDPP_PACKAGE:
		User(ID _id, Connector *_parent);
		~User();

	public:
		String GetName();
	};
}

#endif