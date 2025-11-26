#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

int main(int argc, char** argv) {
    float radius = 2560.0f;
    float target_radius = 200.0f;
    float alpha = 0.0f;
    float target_alpha = 200.0f;
    bool closing = false;

    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_TRANSPARENT);
    InitWindow(0, 0, "Spotlight");
    SetExitKey(0);
    
    int monitor_id = GetCurrentMonitor();
    SetTargetFPS(GetMonitorRefreshRate(monitor_id));
    
    while (!WindowShouldClose()) {
        float t = fminf(GetFrameTime() * 20, 1.0f);
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))  closing = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) closing = true;
        if (GetKeyPressed())                          closing = true;
        
        target_radius = fmaxf(100.0f, target_radius + GetMouseWheelMove() * 10);

        alpha  = Lerp(alpha,  closing ? 0.0f : target_alpha,  t);
        radius = Lerp(radius, closing ? 0.0f : target_radius, t);

        if (closing && alpha < 0.1) break;

        BeginDrawing();
        ClearBackground((Color){0, 0, 0, floorf(alpha + 0.5f)});
        BeginBlendMode(BLEND_CUSTOM);
        rlSetBlendFactorsSeparate(RL_SRC_ALPHA, RL_ONE_MINUS_SRC_ALPHA, RL_FUNC_ADD, RL_ZERO, RL_ONE, RL_FUNC_ADD);
        DrawCircleSector(GetMousePosition(), radius, 0, 360, 60, BLANK);
        EndBlendMode();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}