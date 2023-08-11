#include <raylib.h>

#include <string>
class App {
 public:
  App(int width, int height, std::string title)
      : width(width), height(height), title(title) {}
  virtual bool init() {
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
    return true;
  }
  virtual bool update() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hello, world!", 350, 280, 20, LIGHTGRAY);
    EndDrawing();
    return WindowShouldClose();
  }

  virtual void shutdown() { CloseWindow(); }

  ~App() {}

  int getWidth() const { return width; }
  int getHeight() const { return height; }
  std::string getTitle() const { return title; }

 private:
  int width;
  int height;
  std::string title;
};

bool runApp(App& app) {
  if (!app.init()) return false;
  while (!app.update())
    ;
  app.shutdown();
  return true;
}
int main(void) {
  App app(800, 600, "example");
  runApp(app);
  return 0;
}