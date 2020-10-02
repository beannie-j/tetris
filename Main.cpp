#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <iostream>
#include <cstdlib>
#include <typeinfo>

#include "Tetromino.h"
#include "Button.h"
#include "Menu.h"
#include "TextBox.h"
#include "Layer.h"
#include <sqlite3.h>
#include "Database.h"
#include "Sound.h"
#include "Application.h"
#include "MainMenuLayer.h"

int main()
{
    Application application("Tetris");
    application.Init();
    application.Run();
    application.Shutdown();
}