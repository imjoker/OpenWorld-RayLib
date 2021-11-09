#include "Prop.h"
#include "raymath.h"

Prop::Prop (Vector2 pPos, Texture2D pTex) noexcept: vWorldPos(pPos), vTexture(pTex)
{

}

void 
Prop::Render (Vector2 pKnightPos) noexcept
{
        Vector2 screenPos{ Vector2Subtract (vWorldPos, pKnightPos) };

    DrawTextureEx (vTexture, screenPos, 0.f, sScale, WHITE);
}

Rectangle 
Prop::getCollisionRec (Vector2 pKnightPos) const noexcept
{
        Vector2 screenPos{ Vector2Subtract(vWorldPos, pKnightPos) };

    return Rectangle {screenPos.x, screenPos.y, vTexture.width * sScale, vTexture.height * sScale};
}