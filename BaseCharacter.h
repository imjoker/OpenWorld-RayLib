#pragma once

#include "raylib.h"

class BaseCharacter
{
    public:
                                    BaseCharacter       () noexcept;
                    void            undoMovement        () noexcept;
        virtual     void            tick                (float pDeltaTime) noexcept;
        virtual     Vector2         getScreenPos        () const noexcept = 0;
                    void            setAlive            (bool pIsAlive) noexcept;


                    bool            getAlive            () const noexcept;
                    Vector2         getWorldPos         () const noexcept;
                    Rectangle       getCollisionRec     () noexcept;

    protected:

                    Texture2D   rTexture  {LoadTexture ("characters/knight_idle_spritesheet.png")};
                    Texture2D   rIdle     {LoadTexture ("characters/knight_idle_spritesheet.png")};
                    Texture2D   rRun      {LoadTexture ("characters/knight_run_spritesheet.png")};

                    Vector2     rWorldPos          {};
                    Vector2     rWorldPosLastFrame {};
                    
                    float       rRightLeft         {1.f};   // 1 : facing right, -1 : facing left

                // animation variables

                    float       rRunningTime {};
                    int         rFrame       {};
                    int         rMaxFrames   {6};
                    float       rUpdateTime  {1.f / 12.f};
                    float       rSpeed       {4.f};
                    float       rWidth       {};
                    float       rHeight      {};
                    float       rScale       {4.0f};
                    Vector2     rVelocity    {};

        private:
                    bool        vIsAlive     {true};
};
