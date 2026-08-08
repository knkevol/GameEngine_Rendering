#pragma once

namespace GER
{
	namespace DDD
	{
		struct Material
		{
			LinearColor Diffuse = LinearColor::White;
			LinearColor Specular = LinearColor(0.5f, 0.5f, 0.5f, 1.f);
			float Shininess = 32.f;
		};
	}
}