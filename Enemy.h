#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
    public:

                        Enemy         (Vector2 pPos, Texture2D pIdleTexture, Texture2D pRunTexture) noexcept;

    virtual void        tick          (float pDeltaTime) noexcept override;
            void        setTarget     (Character * pCharacter) noexcept;

    virtual Vector2     getScreenPos  () const noexcept override;

    private:

        Character *  vTarget;
        float        vDamagePerSec {10.f};
        float        vRadius       {25.f};
};