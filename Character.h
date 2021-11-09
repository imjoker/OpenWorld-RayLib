#pragma once

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
    public:

                            Character               (int pWinWidth, int pWinHeight) noexcept;

        virtual void        tick                    (float pDeltaTime) noexcept override;
                void        takeDamage              (float pDamage) noexcept;

        virtual Vector2     getScreenPos            () const noexcept override;
                Rectangle   getWeaponCollisionRec   () const noexcept;
                float       getHealth               () const noexcept;
    private:

        int         vWindowWidth         {};
        int         vWindowHeight        {};
        Texture2D   vWeapon              {LoadTexture("characters/weapon_sword.png")};
        Rectangle   vWeaponCollisionRec  {};
        float       vHealth              {100.f};
};

