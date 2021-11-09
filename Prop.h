#include "raylib.h"

// for rocks, tress, boards etc. (Non-moving collider objects)

class Prop
{

    public:
                        Prop                (Vector2 pPos, Texture2D pTex) noexcept;
            void        Render              (Vector2 pKnightPos) noexcept;
            Rectangle   getCollisionRec     (Vector2 pKnightPos) const noexcept;

    private:

            Vector2     vWorldPos {};
            Texture2D   vTexture  {};

static constexpr  float sScale {4.f};
};