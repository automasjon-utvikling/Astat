#include "atpch.h"
#include "Astat/Astat.h"


void scan (std::vector<uint8_t> a_data)
{

	std::vector<Layer> layers_detected;
	for (auto layer : layers)
	{
		if (layer.match (a_data))
		{
			layers_detected.push_back (layer);
		}
	}

	if (layers_detected.size () = 0)
	{
		// protocol not supported
		return;
	}
	if (layers_detected.size () > 1)
	{
		// multiple protocols detected -> warning to server, fatal client
		return;
	}
	if (layers_detected.size () = 1)
	{
		layers_detected[0].analyse ();
	}
}