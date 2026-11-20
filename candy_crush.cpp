#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace sf;
using namespace std;

// Game State Enum
enum GameState {
    STATE_MENU,
    STATE_INSTRUCTIONS,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_GAMEOVER
};

// Global variables
int gamescore = 0;
int highscore = 0;
int targetscore = 150;
const int Board_size = 8;
const int gem_types = 6;
int Board[Board_size][Board_size];

// Random function for generating random gem
int random(int& a) {
    srand(static_cast<unsigned int>(time(0) + a));
    int x = rand() % gem_types;
    a += 37;
    return x;
}

// Check initial board for same gems
bool SameGemsPresent2(int arr[][8], const int rows = 8, const int colums = 8) {
    int s = 345898;
    bool flag = false;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < colums - 2; j++) {
            if (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2]) {
                arr[i][j] = random(s);
                arr[i][j + 1] = random(s);
                arr[i][j + 2] = random(s);
                flag = true;
            }
        }
    }
    for (int i = 0; i < rows - 2; i++) {
        for (int j = 0; j < colums; j++) {
            if (arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j]) {
                arr[i][j] = random(s);
                arr[i + 1][j] = random(s);
                arr[i + 2][j] = random(s);
                flag = true;
            }
        }
    }
    return flag;
}

// Swapping function for sprites
void swapsprites(Sprite grid[][8], int i, int j, int k, int l) {
    Vector2f pos1 = grid[i][j].getPosition();
    Vector2f pos2 = grid[k][l].getPosition();
    grid[i][j].setPosition(pos2);
    grid[k][l].setPosition(pos1);
    swap(grid[i][j], grid[k][l]);
}

// Match testing function
bool tester(int arr[][8], int a, int b) {
    if (a < 0 || a >= 8 || b < 0 || b >= 8) return false;
    // Down
    if (a < 6 && arr[a][b] == arr[a + 1][b] && arr[a][b] == arr[a + 2][b]) return true;
    // Up
    if (a > 1 && arr[a][b] == arr[a - 1][b] && arr[a][b] == arr[a - 2][b]) return true;
    // Right
    if (b < 6 && arr[a][b] == arr[a][b + 1] && arr[a][b] == arr[a][b + 2]) return true;
    // Left
    if (b > 1 && arr[a][b] == arr[a][b - 1] && arr[a][b] == arr[a][b - 2]) return true;
    // Horizontal middle
    if (b > 0 && b < 7 && arr[a][b] == arr[a][b - 1] && arr[a][b] == arr[a][b + 1]) return true;
    // Vertical middle
    if (a > 0 && a < 7 && arr[a][b] == arr[a - 1][b] && arr[a][b] == arr[a + 1][b]) return true;
    return false;
}

// Destroy 3 gems match
int destroyer(int arr[][8], int a, int b) {
    int c = 83373;
    int points = 0;
    if (a < 6 && arr[a][b] == arr[a + 1][b] && arr[a][b] == arr[a + 2][b]) {
        gamescore += 10; points += 10;
        arr[a][b] = random(c); arr[a + 1][b] = random(c); arr[a + 2][b] = random(c);
    }
    if (a > 1 && arr[a][b] == arr[a - 1][b] && arr[a][b] == arr[a - 2][b]) {
        gamescore += 10; points += 10;
        arr[a][b] = random(c); arr[a - 1][b] = random(c); arr[a - 2][b] = random(c);
    }
    if (b < 6 && arr[a][b] == arr[a][b + 1] && arr[a][b] == arr[a][b + 2]) {
        gamescore += 10; points += 10;
        arr[a][b] = random(c); arr[a][b + 1] = random(c); arr[a][b + 2] = random(c);
    }
    if (b > 1 && arr[a][b] == arr[a][b - 1] && arr[a][b] == arr[a][b - 2]) {
        gamescore += 10; points += 10;
        arr[a][b] = random(c); arr[a][b - 1] = random(c); arr[a][b - 2] = random(c);
    }
    if (b > 0 && b < 7 && arr[a][b] == arr[a][b - 1] && arr[a][b] == arr[a][b + 1]) {
        gamescore += 10; points += 10;
        arr[a][b] = random(c); arr[a][b - 1] = random(c); arr[a][b + 1] = random(c);
    }
    if (a > 0 && a < 7 && arr[a][b] == arr[a + 1][b] && arr[a][b] == arr[a - 1][b]) {
        gamescore += 10; points += 10;
        arr[a][b] = random(c); arr[a + 1][b] = random(c); arr[a - 1][b] = random(c);
    }
    return points;
}

// Destroy 4 gems match
int destroyer2(int arr[][8], int a, int b) {
    int d = 889373;
    int points = 0;
    if (a < 5 && arr[a][b] == arr[a + 1][b] && arr[a][b] == arr[a + 2][b] && arr[a][b] == arr[a + 3][b]) {
        gamescore += 20; points += 20;
        arr[a][b] = random(d); arr[a + 1][b] = random(d); arr[a + 2][b] = random(d); arr[a + 3][b] = random(d);
    }
    if (a > 2 && arr[a][b] == arr[a - 1][b] && arr[a][b] == arr[a - 2][b] && arr[a][b] == arr[a - 3][b]) {
        gamescore += 20; points += 20;
        arr[a][b] = random(d); arr[a - 1][b] = random(d); arr[a - 2][b] = random(d); arr[a - 3][b] = random(d);
    }
    if (b < 5 && arr[a][b] == arr[a][b + 1] && arr[a][b] == arr[a][b + 2] && arr[a][b] == arr[a][b + 3]) {
        gamescore += 20; points += 20;
        arr[a][b] = random(d); arr[a][b + 1] = random(d); arr[a][b + 2] = random(d); arr[a][b + 3] = random(d);
    }
    if (b > 2 && arr[a][b] == arr[a][b - 1] && arr[a][b] == arr[a][b - 2] && arr[a][b] == arr[a][b - 3]) {
        gamescore += 20; points += 20;
        arr[a][b] = random(d); arr[a][b - 1] = random(d); arr[a][b - 2] = random(d); arr[a][b - 3] = random(d);
    }
    return points;
}

// Floating Score Effect Structure
struct FloatingText {
    Text text;
    float alpha;
    Vector2f pos;
    bool active;
};

// UI Button Helper
struct Button {
    RectangleShape shape;
    Text label;
    bool isHovered;

    void setup(Vector2f pos, Vector2f size, string str, Font& font, unsigned int charSize, Color bg, Color outline) {
        shape.setPosition(pos);
        shape.setSize(size);
        shape.setFillColor(bg);
        shape.setOutlineColor(outline);
        shape.setOutlineThickness(2.f);

        label.setFont(font);
        label.setString(str);
        label.setCharacterSize(charSize);
        label.setFillColor(Color::White);

        FloatRect tb = label.getLocalBounds();
        label.setPosition(
            pos.x + (size.x - tb.width) / 2.f - tb.left,
            pos.y + (size.y - tb.height) / 2.f - tb.top
        );
        isHovered = false;
    }

    void update(Vector2f mousePos) {
        if (shape.getGlobalBounds().contains(mousePos)) {
            if (!isHovered) {
                shape.setFillColor(Color(65, 75, 100, 230));
                shape.setOutlineColor(Color(255, 215, 0));
                isHovered = true;
            }
        } else {
            if (isHovered) {
                shape.setFillColor(Color(25, 30, 45, 210));
                shape.setOutlineColor(Color(90, 100, 130));
                isHovered = false;
            }
        }
    }

    bool isClicked(Vector2f mousePos, bool mousePressed) {
        return (shape.getGlobalBounds().contains(mousePos) && mousePressed);
    }

    void draw(RenderWindow& window) {
        window.draw(shape);
        window.draw(label);
    }
};

// Helper to update sprite grid textures
void updateTextures(Sprite grid[][8], int board[][8], Texture textures[]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int val = board[i][j];
            if (val >= 0 && val < gem_types) {
                grid[i][j].setTexture(textures[val]);
            }
        }
    }
}

int main() {
#ifdef _WIN32
    char exePath[MAX_PATH];
    if (GetModuleFileNameA(NULL, exePath, MAX_PATH)) {
        string pathStr(exePath);
        size_t pos = pathStr.find_last_of("\\/");
        if (pos != string::npos) {
            SetCurrentDirectoryA(pathStr.substr(0, pos).c_str());
        }
    }
#endif

    // Window settings
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Candy Crush - PF Project Pro Edition", Style::Close | Style::Titlebar);
    window.setFramerateLimit(60);

    // Read highscore and target
    {
        ifstream finHigh("high.txt");
        if (finHigh >> highscore) {} else { highscore = 0; }
        ifstream finTarget("target.txt");
        if (finTarget >> targetscore && targetscore > 0) {} else { targetscore = 150; }
    }

    // Load Fonts: Full unicode Arial fonts with 100% character coverage
    Font fontTitle, fontBody;
    if (!fontTitle.loadFromFile("arialbd.ttf")) {
        fontTitle.loadFromFile("C:/Windows/Fonts/arialbd.ttf");
    }
    if (!fontBody.loadFromFile("arial.ttf")) {
        fontBody.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    // Load Textures
    Texture gemTextures[gem_types];
    gemTextures[0].loadFromFile("Bejeweled_purple_gem_promotional.png");
    gemTextures[1].loadFromFile("Bejeweled_green_gem_promotional.png");
    gemTextures[2].loadFromFile("Bejeweled_blue_gem_promotional.png");
    gemTextures[3].loadFromFile("Bejeweled_red_gem_promotional.png");
    gemTextures[4].loadFromFile("Bejeweled_orange_gem_promotional.png");
    gemTextures[5].loadFromFile("Bejeweled_white_gem_promotional.png");

    Texture bgTexture;
    bool bgLoaded = bgTexture.loadFromFile("bg_image.jpg");
    Sprite bgSprite;
    if (bgLoaded && bgTexture.getSize().x > 0 && bgTexture.getSize().y > 0) {
        bgSprite.setTexture(bgTexture);
        bgSprite.setScale(
            (float)WINDOW_WIDTH / bgTexture.getSize().x,
            (float)WINDOW_HEIGHT / bgTexture.getSize().y
        );
    }

    // Load Sound Buffers
    SoundBuffer bufClick, bufSelect, bufSwap, bufMatch, bufCombo, bufGameOver;
    Sound sndClick, sndSelect, sndSwap, sndMatch, sndCombo, sndGameOver;

    if (bufClick.loadFromFile("click.wav")) sndClick.setBuffer(bufClick);
    if (bufSelect.loadFromFile("select.wav")) sndSelect.setBuffer(bufSelect);
    if (bufSwap.loadFromFile("swap.wav")) sndSwap.setBuffer(bufSwap);
    if (bufMatch.loadFromFile("match.wav")) sndMatch.setBuffer(bufMatch);
    if (bufCombo.loadFromFile("combo.wav")) sndCombo.setBuffer(bufCombo);
    if (bufGameOver.loadFromFile("gameover.wav")) sndGameOver.setBuffer(bufGameOver);

    sndClick.setVolume(80.f);
    sndSelect.setVolume(85.f);
    sndSwap.setVolume(50.f);
    sndMatch.setVolume(100.f);
    sndCombo.setVolume(100.f);
    sndGameOver.setVolume(90.f);

    // Floating text pool
    vector<FloatingText> floatingTexts;
    auto addFloatingText = [&](Vector2f pos, string msg, Color col) {
        FloatingText ft;
        ft.text.setFont(fontTitle);
        ft.text.setString(msg);
        ft.text.setCharacterSize(22);
        ft.text.setFillColor(col);
        ft.pos = pos;
        ft.text.setPosition(pos);
        ft.alpha = 255.f;
        ft.active = true;
        floatingTexts.push_back(ft);
    };

    // Board Layout constants
    const float BOARD_START_X = 282.f;
    const float BOARD_START_Y = 28.f;
    const float CELL_STEP_X = 62.f;
    const float CELL_STEP_Y = 68.f;
    const float TILE_W = 56.f;
    const float TILE_H = 62.f;

    Sprite sprite_grid[8][8];
    RectangleShape tile_bg[8][8];

    auto initBoard = [&]() {
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < Board_size; ++i) {
            for (int j = 0; j < Board_size; ++j) {
                Board[i][j] = rand() % gem_types;
            }
        }
        while (SameGemsPresent2(Board, 8, 8)) {}

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                float px = BOARD_START_X + j * CELL_STEP_X;
                float py = BOARD_START_Y + i * CELL_STEP_Y;

                tile_bg[i][j].setSize(Vector2f(TILE_W, TILE_H));
                tile_bg[i][j].setPosition(px, py);
                tile_bg[i][j].setFillColor(Color(15, 20, 32, 175));
                tile_bg[i][j].setOutlineColor(Color(255, 255, 255, 30));
                tile_bg[i][j].setOutlineThickness(1.f);

                sprite_grid[i][j].setPosition(px + 2.f, py + 4.f);
                sprite_grid[i][j].setScale(0.23f, 0.23f);
            }
        }
        updateTextures(sprite_grid, Board, gemTextures);
        gamescore = 0;
    };

    initBoard();

    // Game state tracking
    GameState currentState = STATE_MENU;
    int cursorRow = 0, cursorCol = 0;
    bool hasSelected = false;
    int selRow = -1, selCol = -1;
    float totalTime = 60.f;
    float remainingTime = totalTime;
    Clock gameClock;
    bool gameOverSoundPlayed = false;

    // Selection highlight rectangle (Cyan Glowing Frame)
    RectangleShape selHighlight(Vector2f(TILE_W + 4.f, TILE_H + 4.f));
    selHighlight.setFillColor(Color(0, 230, 255, 40));
    selHighlight.setOutlineColor(Color(0, 230, 255));
    selHighlight.setOutlineThickness(3.f);

    // Active Keyboard Cursor Frame (Vibrant Red Glowing Frame)
    RectangleShape cursorFrame(Vector2f(TILE_W + 4.f, TILE_H + 4.f));
    cursorFrame.setFillColor(Color(255, 50, 50, 30));
    cursorFrame.setOutlineColor(Color(255, 50, 50));
    cursorFrame.setOutlineThickness(3.f);

    // Setup Buttons
    Button btnPlay, btnHowTo, btnExitMenu;
    btnPlay.setup(Vector2f(275.f, 240.f), Vector2f(250.f, 50.f), "START GAME", fontTitle, 22, Color(25, 30, 45, 220), Color(247, 183, 49));
    btnHowTo.setup(Vector2f(275.f, 310.f), Vector2f(250.f, 50.f), "HOW TO PLAY", fontTitle, 22, Color(25, 30, 45, 220), Color(90, 100, 130));
    btnExitMenu.setup(Vector2f(275.f, 380.f), Vector2f(250.f, 50.f), "EXIT", fontTitle, 22, Color(25, 30, 45, 220), Color(90, 100, 130));

    Button btnBackInstructions;
    btnBackInstructions.setup(Vector2f(275.f, 515.f), Vector2f(250.f, 48.f), "< BACK TO MENU", fontTitle, 20, Color(25, 30, 45, 230), Color(247, 183, 49));

    Button btnPauseGame, btnMenuGame;
    btnPauseGame.setup(Vector2f(20.f, 545.f), Vector2f(110.f, 36.f), "PAUSE (P)", fontTitle, 13, Color(25, 30, 45, 220), Color(90, 100, 130));
    btnMenuGame.setup(Vector2f(140.f, 545.f), Vector2f(110.f, 36.f), "MENU (ESC)", fontTitle, 13, Color(25, 30, 45, 220), Color(90, 100, 130));

    Button btnResume, btnRestartPause, btnExitPause;
    btnResume.setup(Vector2f(275.f, 230.f), Vector2f(250.f, 48.f), "RESUME", fontTitle, 22, Color(25, 30, 45, 230), Color(247, 183, 49));
    btnRestartPause.setup(Vector2f(275.f, 295.f), Vector2f(250.f, 48.f), "RESTART", fontTitle, 22, Color(25, 30, 45, 230), Color(90, 100, 130));
    btnExitPause.setup(Vector2f(275.f, 360.f), Vector2f(250.f, 48.f), "MAIN MENU", fontTitle, 22, Color(25, 30, 45, 230), Color(90, 100, 130));

    Button btnPlayAgain, btnMenuOver;
    btnPlayAgain.setup(Vector2f(275.f, 380.f), Vector2f(250.f, 48.f), "PLAY AGAIN", fontTitle, 22, Color(25, 30, 45, 230), Color(247, 183, 49));
    btnMenuOver.setup(Vector2f(275.f, 440.f), Vector2f(250.f, 48.f), "MAIN MENU", fontTitle, 22, Color(25, 30, 45, 230), Color(90, 100, 130));

    // UI HUD cards
    RectangleShape hudCardScore(Vector2f(230.f, 85.f));
    hudCardScore.setPosition(20.f, 28.f);
    hudCardScore.setFillColor(Color(18, 24, 36, 215));
    hudCardScore.setOutlineColor(Color(255, 215, 0, 200));
    hudCardScore.setOutlineThickness(2.f);

    RectangleShape hudCardTarget(Vector2f(230.f, 65.f));
    hudCardTarget.setPosition(20.f, 126.f);
    hudCardTarget.setFillColor(Color(18, 24, 36, 215));
    hudCardTarget.setOutlineColor(Color(46, 213, 115, 200));
    hudCardTarget.setOutlineThickness(2.f);

    RectangleShape hudCardHigh(Vector2f(230.f, 65.f));
    hudCardHigh.setPosition(20.f, 204.f);
    hudCardHigh.setFillColor(Color(18, 24, 36, 215));
    hudCardHigh.setOutlineColor(Color(90, 100, 130, 170));
    hudCardHigh.setOutlineThickness(2.f);

    RectangleShape hudCardTimer(Vector2f(230.f, 90.f));
    hudCardTimer.setPosition(20.f, 282.f);
    hudCardTimer.setFillColor(Color(18, 24, 36, 215));
    hudCardTimer.setOutlineColor(Color(255, 71, 87, 200));
    hudCardTimer.setOutlineThickness(2.f);

    // Swap handling lambda
    auto executeSwap = [&](int r1, int c1, int r2, int c2) {
        if (abs(r1 - r2) + abs(c1 - c2) != 1) return;

        swap(Board[r1][c1], Board[r2][c2]);
        swapsprites(sprite_grid, r1, c1, r2, c2);

        bool m1 = tester(Board, r1, c1);
        bool m2 = tester(Board, r2, c2);

        if (!m1 && !m2) {
            // Revert swap if no match
            swap(Board[r1][c1], Board[r2][c2]);
            swapsprites(sprite_grid, r1, c1, r2, c2);
        } else {
            int pts = 0;
            // Four-gem destruction check
            if (tester(Board, r1, c1)) pts += destroyer2(Board, r1, c1);
            if (tester(Board, r2, c2)) pts += destroyer2(Board, r2, c2);

            // Three-gem destruction check
            if (tester(Board, r1, c1)) pts += destroyer(Board, r1, c1);
            if (tester(Board, r2, c2)) pts += destroyer(Board, r2, c2);

            // Crush sound plays loud and clear ONLY on match
            if (pts >= 20) {
                sndCombo.play();
                addFloatingText(Vector2f(BOARD_START_X + c2 * CELL_STEP_X, BOARD_START_Y + r2 * CELL_STEP_Y), "COMBO! +" + to_string(pts), Color(255, 215, 0));
            } else {
                if (pts == 0) pts = 10;
                sndMatch.play();
                addFloatingText(Vector2f(BOARD_START_X + c2 * CELL_STEP_X, BOARD_START_Y + r2 * CELL_STEP_Y), "+" + to_string(pts), Color(46, 213, 115));
            }

            // Cascading balance & extra combo sound
            int cascadeCount = 0;
            while (SameGemsPresent2(Board, 8, 8)) {
                cascadeCount++;
                gamescore += 10;
            }
            if (cascadeCount > 0) {
                sndCombo.play();
                addFloatingText(Vector2f(BOARD_START_X + c2 * CELL_STEP_X, BOARD_START_Y + r2 * CELL_STEP_Y - 20.f), "CASCADE! +" + to_string(cascadeCount * 10), Color(255, 215, 0));
            }

            updateTextures(sprite_grid, Board, gemTextures);

            if (gamescore > highscore) {
                highscore = gamescore;
                ofstream fout("high.txt");
                fout << highscore;
            }
        }
    };

    // Main Game Loop
    while (window.isOpen()) {
        Vector2i mousePixel = Mouse::getPosition(window);
        Vector2f mousePos = window.mapPixelToCoords(mousePixel);
        bool leftMouseClicked = false;

        Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                window.close();
            }

            if (ev.type == Event::MouseButtonPressed && ev.mouseButton.button == Mouse::Left) {
                leftMouseClicked = true;
            }

            // Keyboard navigation
            if (ev.type == Event::KeyPressed) {
                if (ev.key.code == Keyboard::Escape) {
                    if (currentState == STATE_PLAYING) {
                        currentState = STATE_PAUSED;
                    } else if (currentState == STATE_INSTRUCTIONS || currentState == STATE_PAUSED) {
                        currentState = STATE_MENU;
                    }
                }

                if (ev.key.code == Keyboard::P) {
                    if (currentState == STATE_PLAYING) {
                        currentState = STATE_PAUSED;
                    } else if (currentState == STATE_PAUSED) {
                        currentState = STATE_PLAYING;
                        gameClock.restart();
                    }
                }

                if (ev.key.code == Keyboard::R && (currentState == STATE_PLAYING || currentState == STATE_PAUSED)) {
                    initBoard();
                    remainingTime = totalTime;
                    gameClock.restart();
                    currentState = STATE_PLAYING;
                }

                // In-Game Arrow Keys
                if (currentState == STATE_PLAYING) {
                    if (ev.key.code == Keyboard::Left && cursorCol > 0) cursorCol--;
                    if (ev.key.code == Keyboard::Right && cursorCol < 7) cursorCol++;
                    if (ev.key.code == Keyboard::Up && cursorRow > 0) cursorRow--;
                    if (ev.key.code == Keyboard::Down && cursorRow < 7) cursorRow++;

                    if (ev.key.code == Keyboard::Enter) {
                        if (!hasSelected) {
                            selRow = cursorRow;
                            selCol = cursorCol;
                            hasSelected = true;
                        } else {
                            executeSwap(selRow, selCol, cursorRow, cursorCol);
                            hasSelected = false;
                            selRow = -1; selCol = -1;
                        }
                    }
                }
            }
        }

        // State: Menu Logic
        if (currentState == STATE_MENU) {
            btnPlay.update(mousePos);
            btnHowTo.update(mousePos);
            btnExitMenu.update(mousePos);

            if (btnPlay.isClicked(mousePos, leftMouseClicked)) {
                initBoard();
                remainingTime = totalTime;
                gameClock.restart();
                gameOverSoundPlayed = false;
                currentState = STATE_PLAYING;
            } else if (btnHowTo.isClicked(mousePos, leftMouseClicked)) {
                currentState = STATE_INSTRUCTIONS;
            } else if (btnExitMenu.isClicked(mousePos, leftMouseClicked)) {
                window.close();
            }
        }

        // State: Instructions Logic
        else if (currentState == STATE_INSTRUCTIONS) {
            btnBackInstructions.update(mousePos);
            if (btnBackInstructions.isClicked(mousePos, leftMouseClicked)) {
                currentState = STATE_MENU;
            }
        }

        // State: Playing Logic
        else if (currentState == STATE_PLAYING) {
            btnPauseGame.update(mousePos);
            btnMenuGame.update(mousePos);

            if (btnPauseGame.isClicked(mousePos, leftMouseClicked)) {
                currentState = STATE_PAUSED;
            } else if (btnMenuGame.isClicked(mousePos, leftMouseClicked)) {
                currentState = STATE_MENU;
            }

            // Mouse gem selection
            if (leftMouseClicked) {
                if (mousePos.x >= BOARD_START_X && mousePos.x <= BOARD_START_X + 8 * CELL_STEP_X &&
                    mousePos.y >= BOARD_START_Y && mousePos.y <= BOARD_START_Y + 8 * CELL_STEP_Y) {
                    int c = (int)((mousePos.x - BOARD_START_X) / CELL_STEP_X);
                    int r = (int)((mousePos.y - BOARD_START_Y) / CELL_STEP_Y);
                    if (r >= 0 && r < 8 && c >= 0 && c < 8) {
                        cursorRow = r;
                        cursorCol = c;
                        if (!hasSelected) {
                            selRow = r;
                            selCol = c;
                            hasSelected = true;
                        } else {
                            executeSwap(selRow, selCol, r, c);
                            hasSelected = false;
                            selRow = -1; selCol = -1;
                        }
                    }
                }
            }

            // Timer update
            float dt = gameClock.restart().asSeconds();
            remainingTime -= dt;
            if (remainingTime <= 0.f) {
                remainingTime = 0.f;
                currentState = STATE_GAMEOVER;
                if (!gameOverSoundPlayed) {
                    gameOverSoundPlayed = true;
                }
                if (gamescore > highscore) {
                    highscore = gamescore;
                    ofstream fout("high.txt");
                    fout << highscore;
                }
            }

            // Update floating score texts
            for (auto& ft : floatingTexts) {
                if (ft.active) {
                    ft.pos.y -= 35.f * dt;
                    ft.alpha -= 180.f * dt;
                    if (ft.alpha <= 0.f) {
                        ft.active = false;
                    } else {
                        Color col = ft.text.getFillColor();
                        col.a = (Uint8)ft.alpha;
                        ft.text.setFillColor(col);
                        ft.text.setPosition(ft.pos);
                    }
                }
            }
        }

        // State: Paused Logic
        else if (currentState == STATE_PAUSED) {
            btnResume.update(mousePos);
            btnRestartPause.update(mousePos);
            btnExitPause.update(mousePos);

            if (btnResume.isClicked(mousePos, leftMouseClicked)) {
                gameClock.restart();
                currentState = STATE_PLAYING;
            } else if (btnRestartPause.isClicked(mousePos, leftMouseClicked)) {
                initBoard();
                remainingTime = totalTime;
                gameClock.restart();
                currentState = STATE_PLAYING;
            } else if (btnExitPause.isClicked(mousePos, leftMouseClicked)) {
                currentState = STATE_MENU;
            }
        }

        // State: Game Over Logic
        else if (currentState == STATE_GAMEOVER) {
            btnPlayAgain.update(mousePos);
            btnMenuOver.update(mousePos);

            if (btnPlayAgain.isClicked(mousePos, leftMouseClicked)) {
                initBoard();
                remainingTime = totalTime;
                gameClock.restart();
                gameOverSoundPlayed = false;
                currentState = STATE_PLAYING;
            } else if (btnMenuOver.isClicked(mousePos, leftMouseClicked)) {
                currentState = STATE_MENU;
            }
        }

        // ================= RENDERING =================
        window.clear(Color(12, 16, 26));
        if (bgLoaded) {
            window.draw(bgSprite);
        }

        // State: MENU Render
        if (currentState == STATE_MENU) {
            RectangleShape overlay(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
            overlay.setFillColor(Color(10, 14, 24, 215));
            window.draw(overlay);

            Text title("CANDY CRUSH", fontTitle, 48);
            title.setFillColor(Color(255, 215, 0));
            FloatRect tb = title.getLocalBounds();
            title.setPosition((WINDOW_WIDTH - tb.width) / 2.f, 95.f);
            window.draw(title);

            Text subtitle("PROGRAMMING FUNDAMENTALS - PRO EDITION", fontTitle, 15);
            subtitle.setFillColor(Color(180, 200, 225));
            FloatRect sb = subtitle.getLocalBounds();
            subtitle.setPosition((WINDOW_WIDTH - sb.width) / 2.f, 165.f);
            window.draw(subtitle);

            btnPlay.draw(window);
            btnHowTo.draw(window);
            btnExitMenu.draw(window);

            Text highText("ALL-TIME HIGHSCORE: " + to_string(highscore) + "  |  TARGET: " + to_string(targetscore), fontBody, 15);
            highText.setFillColor(Color(200, 205, 215));
            FloatRect hb = highText.getLocalBounds();
            highText.setPosition((WINDOW_WIDTH - hb.width) / 2.f, 470.f);
            window.draw(highText);
        }

        // State: INSTRUCTIONS Render (Clean Two-Card Layout)
        else if (currentState == STATE_INSTRUCTIONS) {
            RectangleShape overlay(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
            overlay.setFillColor(Color(10, 14, 24, 235));
            window.draw(overlay);

            Text header("HOW TO PLAY & GAME RULES", fontTitle, 32);
            header.setFillColor(Color(255, 215, 0));
            FloatRect hb = header.getLocalBounds();
            header.setPosition((WINDOW_WIDTH - hb.width) / 2.f, 30.f);
            window.draw(header);

            // Left Card: Controls
            RectangleShape cardLeft(Vector2f(340.f, 410.f));
            cardLeft.setPosition(45.f, 85.f);
            cardLeft.setFillColor(Color(20, 26, 40, 220));
            cardLeft.setOutlineColor(Color(0, 210, 255, 140));
            cardLeft.setOutlineThickness(2.f);
            window.draw(cardLeft);

            Text titleLeft("CONTROLS & SHORTCUTS", fontTitle, 18);
            titleLeft.setFillColor(Color(0, 210, 255));
            titleLeft.setPosition(65.f, 105.f);
            window.draw(titleLeft);

            string ctrlStr = 
                "[MOUSE CONTROLS]:\n"
                "- Click on any candy to select it.\n"
                "- Click an adjacent candy to swap!\n\n"
                "[KEYBOARD CONTROLS]:\n"
                "- Arrow Keys : Move red cursor\n"
                "- Enter Key  : Select and swap gems\n\n"
                "[KEYBOARD SHORTCUTS]:\n"
                "- 'P' Key    : Pause / Resume game\n"
                "- 'R' Key    : Instant Restart\n"
                "- 'ESC' Key  : Return to Main Menu";

            Text bodyLeft(ctrlStr, fontBody, 14);
            bodyLeft.setFillColor(Color(230, 235, 245));
            bodyLeft.setPosition(65.f, 145.f);
            bodyLeft.setLineSpacing(1.22f);
            window.draw(bodyLeft);

            // Right Card: Rules & Scoring
            RectangleShape cardRight(Vector2f(340.f, 410.f));
            cardRight.setPosition(415.f, 85.f);
            cardRight.setFillColor(Color(20, 26, 40, 220));
            cardRight.setOutlineColor(Color(46, 213, 115, 140));
            cardRight.setOutlineThickness(2.f);
            window.draw(cardRight);

            Text titleRight("RULES & OBJECTIVES", fontTitle, 18);
            titleRight.setFillColor(Color(46, 213, 115));
            titleRight.setPosition(435.f, 105.f);
            window.draw(titleRight);

            string ruleStr = 
                "[MAIN OBJECTIVE]:\n"
                "Swap adjacent candies horizontally or\n"
                "vertically to create matches of 3 or more!\n\n"
                "[SCORING RULES]:\n"
                "- Match 3 Candies : +10 Points\n"
                "- Match 4 Candies : +20 Points (Combo!)\n"
                "- Chain Reactions : Bonus combo points!\n\n"
                "[TIME & TARGET]:\n"
                "- You have 60 SECONDS on the clock.\n"
                "- Target Score    : " + to_string(targetscore) + " Points\n"
                "- Try to beat Highscore: " + to_string(highscore) + " Pts!";

            Text bodyRight(ruleStr, fontBody, 14);
            bodyRight.setFillColor(Color(230, 235, 245));
            bodyRight.setPosition(435.f, 145.f);
            bodyRight.setLineSpacing(1.22f);
            window.draw(bodyRight);

            btnBackInstructions.draw(window);
        }

        // State: PLAYING & PAUSED & GAMEOVER Render
        else {
            // Left HUD Cards
            window.draw(hudCardScore);
            window.draw(hudCardTarget);
            window.draw(hudCardHigh);
            window.draw(hudCardTimer);

            // HUD Text: Score
            Text txtScoreTitle("PLAYER SCORE", fontTitle, 13);
            txtScoreTitle.setFillColor(Color(200, 210, 230));
            txtScoreTitle.setPosition(35.f, 38.f);
            window.draw(txtScoreTitle);

            Text txtScoreVal(to_string(gamescore), fontTitle, 32);
            txtScoreVal.setFillColor(Color(255, 215, 0));
            txtScoreVal.setPosition(35.f, 58.f);
            window.draw(txtScoreVal);

            // HUD Text: Target
            Text txtTargetTitle("TARGET GOAL", fontTitle, 12);
            txtTargetTitle.setFillColor(Color(180, 190, 205));
            txtTargetTitle.setPosition(35.f, 134.f);
            window.draw(txtTargetTitle);

            Text txtTargetVal(to_string(targetscore) + (gamescore >= targetscore ? " (DONE!)" : " PTS"), fontTitle, 18);
            txtTargetVal.setFillColor(gamescore >= targetscore ? Color(46, 213, 115) : Color::White);
            txtTargetVal.setPosition(35.f, 155.f);
            window.draw(txtTargetVal);

            // HUD Text: Highscore
            Text txtHighTitle("ALL-TIME HIGHSCORE", fontTitle, 12);
            txtHighTitle.setFillColor(Color(180, 190, 205));
            txtHighTitle.setPosition(35.f, 212.f);
            window.draw(txtHighTitle);

            Text txtHighVal(to_string(highscore), fontTitle, 18);
            txtHighVal.setFillColor(Color(0, 210, 255));
            txtHighVal.setPosition(35.f, 233.f);
            window.draw(txtHighVal);

            // HUD Text: Timer
            Text txtTimeTitle("TIME REMAINING", fontTitle, 12);
            txtTimeTitle.setFillColor(Color(180, 190, 205));
            txtTimeTitle.setPosition(35.f, 290.f);
            window.draw(txtTimeTitle);

            int secLeft = (int)ceil(remainingTime);
            Text txtTimeVal(to_string(secLeft) + "s", fontTitle, 26);
            txtTimeVal.setFillColor(remainingTime <= 10.f ? Color(255, 71, 87) : (remainingTime <= 25.f ? Color(255, 165, 2) : Color::White));
            txtTimeVal.setPosition(35.f, 310.f);
            window.draw(txtTimeVal);

            // Timer Progress Bar
            float barWidth = 190.f * (remainingTime / totalTime);
            RectangleShape timerBar(Vector2f(max(0.f, barWidth), 7.f));
            timerBar.setPosition(35.f, 348.f);
            timerBar.setFillColor(remainingTime <= 10.f ? Color(255, 71, 87) : (remainingTime <= 25.f ? Color(255, 165, 2) : Color(46, 213, 115)));
            window.draw(timerBar);

            // Controls Hint Box
            RectangleShape hudHint(Vector2f(230.f, 140.f));
            hudHint.setPosition(20.f, 390.f);
            hudHint.setFillColor(Color(15, 20, 32, 190));
            hudHint.setOutlineColor(Color(80, 90, 115, 140));
            hudHint.setOutlineThickness(1.f);
            window.draw(hudHint);

            Text hintTitle("CONTROLS:", fontTitle, 13);
            hintTitle.setFillColor(Color(255, 215, 0));
            hintTitle.setPosition(30.f, 400.f);
            window.draw(hintTitle);

            string hintStr = 
                "- Click or Arrow Keys: Select\n"
                "- Click adjacent/Enter: Swap\n"
                "- 'P' : Pause Game\n"
                "- 'R' : Restart Game\n"
                "- 'ESC' : Main Menu";
            Text hintBody(hintStr, fontBody, 12);
            hintBody.setFillColor(Color(200, 210, 225));
            hintBody.setPosition(30.f, 425.f);
            hintBody.setLineSpacing(1.18f);
            window.draw(hintBody);

            btnPauseGame.draw(window);
            btnMenuGame.draw(window);

            // Render Board: Tile Backgrounds & Candies
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    window.draw(tile_bg[i][j]);
                    window.draw(sprite_grid[i][j]);
                }
            }

            // Draw Selected Gem Highlight (Cyan Glowing Box around tile)
            if (hasSelected && selRow >= 0 && selCol >= 0) {
                float sx = BOARD_START_X + selCol * CELL_STEP_X - 2.f;
                float sy = BOARD_START_Y + selRow * CELL_STEP_Y - 2.f;
                selHighlight.setPosition(sx, sy);
                window.draw(selHighlight);
            }

            // Draw Active Keyboard Cursor Frame (Red Glowing Box around current tile)
            float cx = BOARD_START_X + cursorCol * CELL_STEP_X - 2.f;
            float cy = BOARD_START_Y + cursorRow * CELL_STEP_Y - 2.f;
            cursorFrame.setPosition(cx, cy);
            window.draw(cursorFrame);

            // Draw Floating Score Texts
            for (auto& ft : floatingTexts) {
                if (ft.active) {
                    window.draw(ft.text);
                }
            }

            // Pause Overlay
            if (currentState == STATE_PAUSED) {
                RectangleShape pOverlay(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
                pOverlay.setFillColor(Color(10, 14, 24, 220));
                window.draw(pOverlay);

                Text pTitle("GAME PAUSED", fontTitle, 40);
                pTitle.setFillColor(Color(255, 215, 0));
                FloatRect pb = pTitle.getLocalBounds();
                pTitle.setPosition((WINDOW_WIDTH - pb.width) / 2.f, 130.f);
                window.draw(pTitle);

                btnResume.draw(window);
                btnRestartPause.draw(window);
                btnExitPause.draw(window);
            }

            // Game Over Overlay
            if (currentState == STATE_GAMEOVER) {
                RectangleShape goOverlay(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
                goOverlay.setFillColor(Color(10, 14, 24, 230));
                window.draw(goOverlay);

                bool won = (gamescore >= targetscore);
                Text goTitle(won ? "TARGET REACHED! YOU WIN!" : "TIME'S UP!", fontTitle, 36);
                goTitle.setFillColor(won ? Color(46, 213, 115) : Color(255, 71, 87));
                FloatRect gb = goTitle.getLocalBounds();
                goTitle.setPosition((WINDOW_WIDTH - gb.width) / 2.f, 120.f);
                window.draw(goTitle);

                Text finalScore("FINAL SCORE: " + to_string(gamescore), fontTitle, 26);
                finalScore.setFillColor(Color(255, 215, 0));
                FloatRect fsb = finalScore.getLocalBounds();
                finalScore.setPosition((WINDOW_WIDTH - fsb.width) / 2.f, 190.f);
                window.draw(finalScore);

                string highMsg = (gamescore >= highscore && gamescore > 0) ? "NEW ALL-TIME HIGHSCORE!" : "HIGHSCORE: " + to_string(highscore);
                Text highDisp(highMsg, fontTitle, 19);
                highDisp.setFillColor(Color(0, 210, 255));
                FloatRect hdb = highDisp.getLocalBounds();
                highDisp.setPosition((WINDOW_WIDTH - hdb.width) / 2.f, 240.f);
                window.draw(highDisp);

                Text targetDisp("TARGET WAS: " + to_string(targetscore) + " PTS", fontTitle, 17);
                targetDisp.setFillColor(Color(180, 190, 210));
                FloatRect tdb = targetDisp.getLocalBounds();
                targetDisp.setPosition((WINDOW_WIDTH - tdb.width) / 2.f, 285.f);
                window.draw(targetDisp);

                btnPlayAgain.draw(window);
                btnMenuOver.draw(window);
            }
        }

        window.display();
    }

    return 0;
}
