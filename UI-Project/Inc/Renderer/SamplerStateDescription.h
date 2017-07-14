#pragma once

#include "Enums.h"
#include "../Util/types.h"
#include "../Math/Color.h"

namespace Pyro
{
	struct SamplerStateDescription {
		SamplerStateDescription();

		bool operator ==(const SamplerStateDescription& rhs) const;
		bool operator !=(const SamplerStateDescription& rhs) const;

		TextureFilterMode textureFilterMode;
		TextureWrapMode textureWrapMode;
		Color color;
	};
}