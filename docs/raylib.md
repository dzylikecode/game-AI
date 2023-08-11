基本结构:

```cpp
class BaseApplication {
 public:
  BaseApplication(const String& applicationTitle = "");
  virtual ~BaseApplication();

  void run();

  virtual void init();
  virtual bool update();
  virtual void shutdown();

  void setClosed(const bool closed);

 private:
  String m_applicationTitle;

 private:
  bool setup();
  void close();
  void main();
};

void BaseApplication::run() {
  if (!setup()) return;
  main();
  close();
}

void BaseApplication::main() {
  init();
  while (!update())
    ;
  shutdown();
}
```

update 必须有 draw 的部分, 不然会阻塞

```cpp
bool BaseApplication::update() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  EndDrawing();
  return WindowShouldClose();
}
```

[sunface/rust-course: “连续六年成为全世界最受喜爱的语言，无 GC 也无需手动内存管理、极高的性能和安全性、过程/OO/函数式编程、优秀的包管理、JS 未来基石" — 工作之余的第二语言来试试 Rust 吧。<<Rust 语言圣经>>拥有全面且深入的讲解、生动贴切的示例、德芙般丝滑的内容，甚至还有 JS 程序员关注的 WASM 和 Deno 等专题。这可能是目前最用心的 Rust 中文学习教程 / Book](https://github.com/sunface/rust-course)

[(9) Raylib Camera2D Overview - YouTube](https://www.youtube.com/watch?v=zkjDU3zmk40&list=PLowVbpI_vWxQkLI6mv4eTZ-Rm-4EV0YbZ&index=5)

[(9) Porting my game written in C to the web using Raylib, WASM, and more! - YouTube](https://www.youtube.com/watch?v=j6rlTtGrld4)
