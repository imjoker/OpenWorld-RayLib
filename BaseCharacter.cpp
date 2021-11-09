#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter () noexcept
{
    
}

void 
BaseCharacter::undoMovement () noexcept
{
    rWorldPos = rWorldPosLastFrame;
}

Rectangle 
BaseCharacter::getCollisionRec () noexcept
{
    return Rectangle{
        getScreenPos ().x,
        getScreenPos ().y,
        rWidth * rScale,
        rHeight * rScale
    };
}

void 
BaseCharacter::tick (float pDeltaTime) noexcept
{
    rWorldPosLastFrame = rWorldPos;

    // update animation frame
    rRunningTime += pDeltaTime;

    if (rRunningTime >= rUpdateTime) {

        rFrame++;

        rRunningTime = 0.f;

        if (rFrame > rMaxFrames)
            rFrame = 0;
    }

    if (Vector2Length (rVelocity) != 0.0) {

        // set worldPos = worldPos + velocity

        rWorldPos = Vector2Add (rWorldPos, Vector2Scale (Vector2Normalize (rVelocity), rSpeed));

        rVelocity.x < 0.f ? rRightLeft = -1.f : rRightLeft = 1.f;

        rTexture = rRun;

    } else
        rTexture = rIdle;

    rVelocity = {};

    // draw the character
    Rectangle source {rFrame * rWidth, 0.f, rRightLeft * rWidth, rHeight};
    Rectangle dest   {getScreenPos ().x, getScreenPos ().y, rScale * rWidth, rScale * rHeight};

    DrawTexturePro (rTexture, source, dest, Vector2{}, 0.f, WHITE);
}

Vector2
BaseCharacter::getWorldPos () const noexcept
{ 
    return rWorldPos;
}

bool
BaseCharacter::getAlive () const noexcept
{ 
    return vIsAlive;
}

void
BaseCharacter::setAlive (bool pIsAlive) noexcept 
{ 
    vIsAlive = pIsAlive; 
}