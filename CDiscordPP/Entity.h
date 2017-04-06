#ifndef __CDISCORDPP_ENTITY_H__
#	define __CDISCORDPP_ENTITY_H__

namespace CDiscordPP
{
	template < class _T >
	class Entity
	{
	private:
		ID id;
		typename _T *parent;

		Entity();
		Entity(const Entity &);
		Entity & operator = (const Entity &);

	CDISCORDPP_PACKAGE:
		Entity(ID _id, typename _T *_parent) : id(_id), parent(_parent)
		{
			//
		}

	public:
		ID GetID()
		{
			return id;
		}

		typename _T *GetParent()
		{
			return parent;
		}

	};
}
#endif