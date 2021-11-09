#include "Character.h"
#include "raymath.h"

Character::Character(int pWinWidth, int pWinHeight) noexcept : vWindowWidth(pWinWidth), vWindowHeight(pWinHeight)
{
    rWidth  = rTexture.width / rMaxFrames;
    rHeight = rTexture.height;
}

void 
Character::tick (float pDeltaTime) noexcept
{

        Vector2 origin{};
        Vector2 offset{};
        float   rotation{};

    if (!getAlive ()) 
        return;

    if (IsKeyDown (KEY_A))
        rVelocity.x -= 1.0;
    if (IsKeyDown (KEY_D))
        rVelocity.x += 1.0;
    if (IsKeyDown (KEY_W))
        rVelocity.y -= 1.0;
    if (IsKeyDown (KEY_S))
        rVelocity.y += 1.0;

    BaseCharacter::tick (pDeltaTime);

    if (rRightLeft > 0.f) {

        origin = {0.f, vWeapon.height * rScale};
        offset = {35.f, 55.f};

        vWeaponCollisionRec = {
            getScreenPos ().x + offset.x,
            getScreenPos ().y + offset.y - vWeapon.height * rScale,
            vWeapon.width * rScale,
            vWeapon.height * rScale
        };

        rotation = IsMouseButtonDown (MOUSE_LEFT_BUTTON) ? 35.f : 0.f;

    } else {

        origin = {vWeapon.width * rScale, vWeapon.height * rScale};
        offset = {25.f, 55.f};

        vWeaponCollisionRec = {
            getScreenPos ().x + offset.x - vWeapon.width * rScale,
            getScreenPos ().y + offset.y - vWeapon.height * rScale,
            vWeapon.width * rScale,
            vWeapon.height * rScale
        };

        rotation = IsMouseButtonDown (MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    }

    // draw the sword
    Rectangle source {0.f, 0.f, static_cast<float>(vWeapon.width) * rRightLeft, static_cast<float>(vWeapon.height)};
    Rectangle dest   {getScreenPos ().x + offset.x, getScreenPos ().y + offset.y, vWeapon.width * rScale, vWeapon.height * rScale};

    DrawTexturePro (vWeapon, source, dest, origin, rotation, WHITE);
}

void 
Character::takeDamage (float pDamage) noexcept
{
    vHealth -= pDamage;

    if (vHealth <= 0.f)
        setAlive(false);
}

Vector2 
Character::getScreenPos () const noexcept
{
    return Vector2{
        static_cast<float>(vWindowWidth) / 2.0f - rScale * (0.5f * rWidth),
        static_cast<float>(vWindowHeight) / 2.0f - rScale * (0.5f * rHeight)
    };
} 

Rectangle
Character::getWeaponCollisionRec () const noexcept
{
    return vWeaponCollisionRec;
}

float
Character::getHealth () const noexcept
{ 
    return vHealth; 
}
