#pragma once
#include "GameResource/ResourceSprite.hpp"
#include "GameResource/Implement/ResourceBaseImpl.hpp"

namespace LuaSTGPlus
{
	class ResourceSpriteImpl : public ResourceBaseImpl<IResourceSprite>
	{
	private:
		Core::ScopeObject<Core::Graphics::ISprite> m_sprite;
		BlendMode m_BlendMode = BlendMode::MulAlpha;
		double m_HalfSizeX = 0.0;
		double m_HalfSizeY = 0.0;
		bool m_bRectangle = false;
	public:
		Core::Graphics::ISprite* GetSprite() { return m_sprite.get(); }
		BlendMode GetBlendMode() { return m_BlendMode; }
		void SetBlendMode(BlendMode m) { m_BlendMode = m; }
		double GetHalfSizeX() { return m_HalfSizeX; }
		double GetHalfSizeY() { return m_HalfSizeY; }
		bool IsRectangle() { return m_bRectangle; }
	public:
		ResourceSpriteImpl(const char* name, Core::Graphics::ISprite* sprite, double hx, double hy, bool rect);
	};
}
