#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Engine/Core/Engine.h"
#include "Core/GameLoader.h"

int main(int, char* [])
{
    const diji::Engine engine("../AllCatsMustRoll/Resources/", "All Cats MUST ROLL");
    engine.Run(GameLoader::GameStartUp);

    return 0;
}
