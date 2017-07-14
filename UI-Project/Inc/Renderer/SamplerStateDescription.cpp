#include "SamplerStateDescription.h"

namespace Pyro
{
	SamplerStateDescription::SamplerStateDescription() :
		textureFilterMode(TextureFilterMode::Default),
		textureWrapMode(TextureWrapMode::Wrap),
		color(Color::White()){}

	bool SamplerStateDescription::operator ==(const SamplerStateDescription& rhs) const {
		bool success = true;
		success &= textureFilterMode == rhs.textureFilterMode;
		success &= textureWrapMode == rhs.textureWrapMode;
		return success;
	}

	bool SamplerStateDescription::operator !=(const SamplerStateDescription& rhs) const {
		return !(*this == rhs);
	}
}