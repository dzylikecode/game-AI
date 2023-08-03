#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <stdio.h>

struct PosColorVertex {
  float x;
  float y;
  float z;
  uint32_t abgr;
};

static PosColorVertex cubeVertices[] = {
    {-1.0f, 1.0f, 1.0f, 0xff000000},   {1.0f, 1.0f, 1.0f, 0xff0000ff},
    {-1.0f, -1.0f, 1.0f, 0xff00ff00},  {1.0f, -1.0f, 1.0f, 0xff00ffff},
    {-1.0f, 1.0f, -1.0f, 0xffff0000},  {1.0f, 1.0f, -1.0f, 0xffff00ff},
    {-1.0f, -1.0f, -1.0f, 0xffffff00}, {1.0f, -1.0f, -1.0f, 0xffffffff},
};

static const uint16_t cubeTriList[] = {
    0, 1, 2, 1, 3, 2, 4, 6, 5, 5, 6, 7, 0, 2, 4, 4, 2, 6,
    1, 5, 3, 5, 7, 3, 0, 4, 1, 4, 5, 1, 2, 3, 6, 6, 3, 7,
};

bgfx::ShaderHandle loadShader(const char *FILENAME) {
  const char *shaderPath = "???";

  switch (bgfx::getRendererType()) {
    case bgfx::RendererType::Noop:
    case bgfx::RendererType::Direct3D9:
      shaderPath = "shaders/dx9/";
      break;
    case bgfx::RendererType::Direct3D11:
    case bgfx::RendererType::Direct3D12:
      shaderPath = "shaders/dx11/";
      break;
    case bgfx::RendererType::Gnm:
      shaderPath = "shaders/pssl/";
      break;
    case bgfx::RendererType::Metal:
      shaderPath = "shaders/metal/";
      break;
    case bgfx::RendererType::OpenGL:
      shaderPath = "shaders/glsl/";
      break;
    case bgfx::RendererType::OpenGLES:
      shaderPath = "shaders/essl/";
      break;
    case bgfx::RendererType::Vulkan:
      shaderPath = "shaders/spirv/";
      break;
  }

  size_t shaderLen = strlen(shaderPath);
  size_t fileLen = strlen(FILENAME);
  char *filePath = (char *)malloc(shaderLen + fileLen);
  memcpy(filePath, shaderPath, shaderLen);
  memcpy(&filePath[shaderLen], FILENAME, fileLen);

  FILE *file = fopen(FILENAME, "rb");
  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  const bgfx::Memory *mem = bgfx::alloc(fileSize + 1);
  fread(mem->data, 1, fileSize, file);
  mem->data[mem->size - 1] = '\0';
  fclose(file);

  return bgfx::createShader(mem);
}

SDL_Window *window = NULL;
const int WIDTH = 640;
const int HEIGHT = 480;
int main(int argc, char *args[]) {
  // Initialize SDL systems
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    // Create a window
    window = SDL_CreateWindow("BGFX Tutorial", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
  }
  bgfx::PlatformData pd;
  memset(&pd, 0, sizeof(pd));
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
  pd.ndt = SDL_GL_GetProcAddress("glXGetCurrentContext");
  pd.nwh = (void *)(uintptr_t)SDL_GetWindowID(window);
#elif BX_PLATFORM_OSX
  pd.ndt = NULL;
  pd.nwh = SDL_GetMetalLayer(window);
#elif BX_PLATFORM_WINDOWS
  pd.ndt = NULL;
  pd.nwh = SDL_SysWMinfo.info.win.window;
#elif BX_PLATFORM_STEAMLINK
  pd.ndt = SDL_GL_GetProcAddress("eglGetCurrentContext");
  pd.nwh = SDL_GL_GetProcAddress("eglGetCurrentDisplay");
#elif BX_PLATFORM_ANDROID
  pd.ndt = NULL;
  pd.nwh = window;
#elif BX_PLATFORM_RPI
  pd.ndt = EGL_DEFAULT_DISPLAY;
  pd.nwh = NULL;
#elif BX_PLATFORM_EMSCRIPTEN
  pd.ndt = NULL;
  pd.nwh = NULL;
#endif
  bgfx::Init bgfxInit;
  bgfxInit.type = bgfx::RendererType::Count;
  bgfxInit.resolution.width = WIDTH;
  bgfxInit.resolution.height = HEIGHT;
  bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
  bgfx::init(bgfxInit);

  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f,
                     0);
  bgfx::setViewRect(0, 0, 0, WIDTH, HEIGHT);

  bgfx::VertexDecl pcvDecl;
  pcvDecl.begin()
      .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
      .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
      .end();
  bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(
      bgfx::makeRef(cubeVertices, sizeof(cubeVertices)), pcvDecl);
  bgfx::IndexBufferHandle ibh =
      bgfx::createIndexBuffer(bgfx::makeRef(cubeTriList, sizeof(cubeTriList)));

  bgfx::ShaderHandle vsh = loadShader("vs_cubes.bin");
  bgfx::ShaderHandle fsh = loadShader("fs_cubes.bin");
  bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh, true);
  // Poll for events and wait till user closes window
  bool quit = false;
  SDL_Event currentEvent;
  while (!quit) {
    while (SDL_PollEvent(&currentEvent) != 0) {
      if (currentEvent.type == SDL_QUIT) {
        quit = true;
      }
    }
  }

  // Free up window
  SDL_DestroyWindow(window);
  // Shutdown SDL
  SDL_Quit();

  return 0;
}