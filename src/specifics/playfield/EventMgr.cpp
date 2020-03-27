#include "EventMgr.h"

void EventMgr::AddDeath(eDeathType cause_, std::shared_ptr<Object> dead_, std::shared_ptr<Germ> killer_)
{
	deaths.push_back(DeathData(cause_, dead_, killer_));
}

DeathData& EventMgr::GetDeath()
{
	if (deaths.size() > 0)
	{
		return deaths[deaths.size() - 1];
	}
}

void EventMgr::RemoveLastDeath()
{
	if (deaths.size() > 0)
	{
		deaths.pop_back();
	}
}

void EventMgr::ClearDeaths()
{
	deaths.clear();
}

bool EventMgr::AreStillDeaths()
{
	if (deaths.size() > 0) return true;
	else return false;
}
