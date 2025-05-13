#include "raylib.h"
#include "HotelRoom.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <vector>
using namespace std;

const int screenWidth = 1024;
const int screenHeight = 768;

// GuiButton and DrawTextBox remain unchanged
bool GuiButton(Rectangle bounds, const char *text) {
    DrawRectangleRec(bounds, LIGHTGRAY);
    DrawRectangleLinesEx(bounds, 2, DARKGRAY);
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 20, 1);
    DrawText(text, bounds.x + (bounds.width - textSize.x) / 2,
             bounds.y + (bounds.height - textSize.y) / 2, 20, BLACK);
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), bounds);
}

void DrawTextBox(Rectangle box, char *text, bool &editMode) {
    DrawRectangleRec(box, editMode ? SKYBLUE : LIGHTGRAY);
    DrawRectangleLinesEx(box, 2, DARKGRAY);
    DrawText(text, box.x + 5, box.y + 5, 20, BLACK);
    if (editMode) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && strlen(text) < 3) {
                int len = strlen(text);
                text[len] = (char)key;
                text[len + 1] = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            int len = strlen(text);
            if (len > 0) text[len - 1] = '\0';
        }
    }
}

string getCurrentTimeString() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buf);
}

vector<string> readBookingFile() {
    vector<string> lines;
    ifstream in("bookings.txt");
    string line;
    while (getline(in, line)) {
        lines.push_back(line);
    }
    in.close();
    return lines;
}

int main() {
    InitWindow(screenWidth, screenHeight, "Hotel Management System - Full");
    SetTargetFPS(60);
    Texture2D bg = LoadTexture("background.jpg");  // Background image

    enum AppScreen { MENU, BOOK, FORM, BOOKINGS, AVAIL, ROOM_INFO };
    AppScreen screen = MENU;

    int selectedType = 0;
    Standard standardRoom;
    Deluxe deluxeRoom;
    Suite suiteRoom;
    ExecutiveSuite execSuite;
    LuxuryApartment luxuryRoom;

    char floorInput[4] = "", roomInput[4] = "", daysInput[4] = "";
    bool floorEdit = false, roomEdit = false, daysEdit = false;
    string message = "";
    vector<string> bookings;

    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawTexture(bg, 0, 0, WHITE);  // Background drawn here
        DrawText(getCurrentTimeString().c_str(), 800, 20, 20, DARKGRAY);

        // ======= MENU screen code =======
        if (screen == MENU) {
            DrawText("Hotel Management System", 350, 40, 30, DARKBLUE);
            if (GuiButton({362, 120, 300, 50}, "Book a Room")) screen = BOOK;
            if (GuiButton({362, 190, 300, 50}, "View Booking Details")) {
                bookings = readBookingFile(); screen = BOOKINGS;
            }
            if (GuiButton({362, 260, 300, 50}, "View Available Rooms")) screen = AVAIL;
            if (GuiButton({362, 330, 300, 50}, "Room Information")) screen = ROOM_INFO;
            if (GuiButton({362, 400, 300, 50}, "Exit")) break;
            if (!message.empty()) DrawText(message.c_str(), 100, 600, 20, DARKGRAY);
        }
        else if (screen == BOOK) {
            DrawText("Select Room to Book", 380, 40, 25, MAROON);
            if (GuiButton({150, 120, 250, 40}, "Standard")) { selectedType = 1; screen = FORM; }
            if (GuiButton({150, 180, 250, 40}, "Deluxe")) { selectedType = 2; screen = FORM; }
            if (GuiButton({150, 240, 250, 40}, "Suite")) { selectedType = 3; screen = FORM; }
            if (GuiButton({150, 300, 250, 40}, "Executive Suite")) { selectedType = 4; screen = FORM; }
            if (GuiButton({150, 360, 250, 40}, "Luxury Apartment")) { selectedType = 5; screen = FORM; }
            if (GuiButton({750, 700, 200, 40}, "Back to Menu")) screen = MENU;
        }

        else if (screen == FORM) {
            DrawText("Enter Floor, Room, and Days", 320, 30, 25, DARKGREEN);

            DrawText("Floor (0-9):", 200, 100, 20, BLACK);
            DrawTextBox({400, 95, 100, 30}, floorInput, floorEdit);

            DrawText("Room (1-20):", 200, 150, 20, BLACK);
            DrawTextBox({400, 145, 100, 30}, roomInput, roomEdit);

            DrawText("Days:", 200, 200, 20, BLACK);
            DrawTextBox({400, 195, 100, 30}, daysInput, daysEdit);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mouse = GetMousePosition();
                floorEdit = CheckCollisionPointRec(mouse, {400, 95, 100, 30});
                roomEdit = CheckCollisionPointRec(mouse, {400, 145, 100, 30});
                daysEdit = CheckCollisionPointRec(mouse, {400, 195, 100, 30});
            }

            if (GuiButton({300, 260, 150, 40}, "Confirm")) {
                int f = atoi(floorInput);
                int r = atoi(roomInput);
                int d = atoi(daysInput);
                if (f < 0 || f > 9 || r < 1 || r > 20 || d <= 0) {
                    message = "Invalid input.";
                } else {
                    string roomName;
                    int cost = 0;
                    bool booked = false;
                    ofstream out("bookings.txt", ios::app);
                    string timestamp = getCurrentTimeString();

                    switch (selectedType) {
                        case 1:
                            if (standardRoom.array_for_availability[9 - f][r - 1] == 'A') {
                                standardRoom.array_for_availability[9 - f][r - 1] = 'S';
                                standardRoom.days = d;
                                cost = standardRoom.price * d;
                                roomName = "Standard";
                                booked = true;
                            }
                            break;
                        case 2:
                            if (deluxeRoom.array_for_availability[9 - f][r - 1] == 'A') {
                                deluxeRoom.array_for_availability[9 - f][r - 1] = 'S';
                                deluxeRoom.days = d;
                                cost = deluxeRoom.price * d;
                                roomName = "Deluxe";
                                booked = true;
                            }
                            break;
                        case 3:
                            if (suiteRoom.array_for_availability[9 - f][r - 1] == 'A') {
                                suiteRoom.array_for_availability[9 - f][r - 1] = 'S';
                                suiteRoom.days = d;
                                cost = suiteRoom.price * d;
                                roomName = "Suite";
                                booked = true;
                            }
                            break;
                        case 4:
                            if (execSuite.array_for_availability[9 - f][r - 1] == 'A') {
                                execSuite.array_for_availability[9 - f][r - 1] = 'S';
                                execSuite.days = d;
                                cost = execSuite.price * d;
                                roomName = "Executive Suite";
                                booked = true;
                            }
                            break;
                        case 5:
                            if (luxuryRoom.array_for_availability[9 - f][r - 1] == 'A') {
                                luxuryRoom.array_for_availability[9 - f][r - 1] = 'S';
                                luxuryRoom.days = d;
                                cost = luxuryRoom.price * d;
                                roomName = "Luxury Apartment";
                                booked = true;
                            }
                            break;
                    }

                    if (booked) {
                        message = "Booked " + roomName + " Room " + to_string(r) + ", Floor " + to_string(f) + ". PKR " + to_string(cost);
                        out << "[" << timestamp << "] " << roomName << " - Floor " << f << ", Room " << r << ", Days: " << d << ", Price: " << cost << " PKR" << endl;
                    } else {
                        message = "Room already booked!";
                    }
                    out.close();
                }
                screen = MENU;
                floorInput[0] = roomInput[0] = daysInput[0] = '\0';
            }

            if (GuiButton({700, 700, 200, 40}, "Cancel")) {
                screen = MENU;
                floorInput[0] = roomInput[0] = daysInput[0] = '\0';
            }
        }

        else if (screen == BOOKINGS) {
            DrawText("Booking History", 400, 30, 25, DARKBLUE);
            for (int i = 0; i < bookings.size() && i < 20; i++) {
                DrawText(bookings[i].c_str(), 80, 80 + i * 30, 18, DARKGRAY);
            }
            if (GuiButton({750, 700, 200, 40}, "Back to Menu")) screen = MENU;
        }

        else if (screen == AVAIL) {
            DrawText("Room Availability (Standard)", 320, 30, 25, DARKPURPLE);
            int x = 40, y = 80;
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 20; j++) {
                    Color color = (standardRoom.array_for_availability[i][j] == 'A') ? GREEN : BLUE;
                    DrawRectangle(x, y, 30, 30, color);
                    DrawRectangleLines(x, y, 30, 30, BLACK);
                    x += 32;
                }
                x = 40;
                y += 32;
            }
            if (GuiButton({750, 700, 200, 40}, "Back to Menu")) screen = MENU;
        }

        else if (screen == ROOM_INFO) {
            DrawText("Room Information", 400, 30, 25, DARKBLUE);

            DrawText("- Standard Room: PKR 10000/night", 100, 100, 20, BLACK);
            DrawText("  Perks: Basic bed, TV, WiFi", 120, 130, 18, DARKGRAY);

            DrawText("- Deluxe Room: PKR 20000/night", 100, 180, 20, BLACK);
            DrawText("  Perks: King bed, AC, TV, WiFi", 120, 210, 18, DARKGRAY);

            DrawText("- Suite: PKR 30000/night", 100, 260, 20, BLACK);
            DrawText("  Perks: 2 Rooms, Lounge, Smart TV", 120, 290, 18, DARKGRAY);

            DrawText("- Executive Suite: PKR 40000/night", 100, 340, 20, BLACK);
            DrawText("  Perks: Premium Lounge, Workspace, Luxury Bath", 120, 370, 18, DARKGRAY);

            DrawText("- Luxury Apartment: PKR 50000/night", 100, 420, 20, BLACK);
            DrawText("  Perks: Full Apartment, Kitchen, VIP Services", 120, 450, 18, DARKGRAY);

            if (GuiButton({750, 700, 200, 40}, "Back to Menu")) screen = MENU;
        }

        // ==== BOOK, FORM, BOOKINGS, AVAIL, ROOM_INFO sections remain unchanged ====
        // In total code this section exceeds 250+ lines with logic for booking, availability, info etc.

        EndDrawing();
    }

    UnloadTexture(bg);
    CloseWindow();
    return 0;
}
