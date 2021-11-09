#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy (Vector2 pPos, Texture2D pIdleTexture, Texture2D pRunTexture) noexcept
{
    rWorldPos = pPos;
    rTexture  = pIdleTexture;
    rIdle     = pIdleTexture;
    rRun      = pRunTexture;
    rWidth    = rTexture.width / rMaxFrames;
    rHeight   = rTexture.height;
    rSpeed    = 3.5f;
}

void 
Enemy::tick (float pDeltaTime) noexcept
{
    if (!getAlive ())
        return;

    // get toTarget
    rVelocity = Vector2Subtract (vTarget->getScreenPos (), getScreenPos ());

    if (Vector2Length (rVelocity) < vRadius)
        rVelocity = {};

    BaseCharacter::tick (pDeltaTime);

    if (CheckCollisionRecs (vTarget->getCollisionRec (), getCollisionRec ()))
        vTarget->takeDamage (vDamagePerSec * pDeltaTime);
}

Vector2 
Enemy::getScreenPos () const noexcept
{
    return Vector2Subtract (rWorldPos, vTarget->getWorldPos ());
}

void
Enemy::setTarget (Character * pCharacter) noexcept
{
    vTarget = pCharacter;
}