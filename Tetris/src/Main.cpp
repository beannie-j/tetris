#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <iostream>
#include <cstdlib>
#include <typeinfo>

#include "Tetromino.h"
#include "../../util/src/Button.h"
#include "../../util/src/Menu.h"
#include "../../util/src/TextBox.h"
#include "../../Layers/src/Layer.h"
#include <sqlite3.h>
#include "../../util/src/Database.h"
#include "../../util/src/Sound.h"
#include "Application.h"
#include "../../Layers/src/MainMenuLayer.h"

int main()
{
    Application application("Tetris");
    application.Init();
    application.Run();
    application.Shutdown();
}