#ifndef __CDISCORDPP_ROLE_H__
#	define __CDISCORDPP_ROLE_H__

namespace CDiscordPP
{
	class Role : public Entity<Guild>
	{
	private:
		String name;

		Role();
		Role(const Role &);
		Role & operator = (const Role &);

	CDISCORDPP_PACKAGE:
		Role(ID _id, Guild *_parent);
		~Role();

	public:
		String GetName();

	};
}

#endif