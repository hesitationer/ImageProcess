#include "common.h"

Common::Common()
{
}

Common::~Common()
{
}
int Common::checkOverFlow(int r)
{
	if (r < 0)
	{
		return 0;
	}

	if (r > 255)
	{
		return 255;
	}

	return r;
}