#ifndef __OPENGL_HELPER__
#define __OPENGL_HELPER__

#include <glad/glad.h>   // for glad
#include <GLFW/glfw3.h>  // for glfw
#include <glm/glm.hpp>
// #define GLM_ENABLE_EXPERIMENTAL
// #include <glm/gtx/string_cast.hpp>

#include <cstdlib>   // for exit
#include <fstream>   // for std::ifstream
#include <sstream>   // for std::stringstream
#include <iostream>  // for std::cout
#include <functional> // for function

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

// if you are macOS, please uncomment fellow define code
// #define IS_MAC_OS
#define INFO_LOG_SIZE 512

// namespace helper
namespace helper {

// // initial opengl
// void initial_glfw();
// // initial glad
// void initial_glad();
// // initial imgui
// void initial_imgui(GLFWwindow *window);
// // inital opengl
// void initial_opengl(std::function<void(void)> set_window, GLFWwindow *&window);
// // set vao
// void set_vao(GLuint &VAO, GLuint &VBO, GLuint &EBO,
//              std::function<void(GLuint, GLuint, GLuint)> set_buffer,
//              bool is_buffer_need_initial = true);

// // check if shader works well
// typedef PFNGLGETSHADERIVPROC CheckShaderHasErrorFunc;
// typedef PFNGLGETSHADERINFOLOGPROC GetShaderErrorMessageFunc;
// void check_shader_have_error(GLuint id, GLenum type,
//                              CheckShaderHasErrorFunc check_has_error,
//                              GetShaderErrorMessageFunc get_error_info);
// // compile vertex shader
// GLuint compile_vertex_shader(std::string path);
// // compile fragment shader
// GLuint compile_fragment_shader(std::string path);
// // compile shader
// GLuint compile_shader(GLenum type, std::string path);
// // create program and link shader
// GLuint create_program_with_shader(GLuint vertex_shader, GLuint fragment_shader);
// // create program and link shader with file path
// GLuint create_program_with_shader(std::string vertex_shader_path,
//                                   std::string fragment_shader_path);
// // create texture with file path
// void create_texture(GLuint &texture, std::string file_path);
// // set int
// void set_shader_int(GLuint id, const std::string &name, int value);
// // set mat4
// void set_shader_mat4(GLuint id, const std::string &name, const glm::mat4 &mat);

/* 
 * 
 * COMMON FUNCTIONS
 * 
 * 
 * 
 * */

// return some info
std::string version() { return "OpenGL Helper 0.0.1 by jskyzero"; }

// exit with exit code check
void exit_program(int exit_code) {
  glfwTerminate();
  exit(0);
}
// commen exit
void exit_program() { exit_program(0); }

// exit with error message
void exit_program(std::string exit_message) {
  std::cout << exit_message << std::endl;
  exit_program(-1);
}

// test if error
void assert_true(bool isOK, std::string error_message) {
  if (isOK) return;
  exit_program(error_message);
}

// read string from path
std::string read_string_from_path(std::string path) {
  std::ifstream in;
  std::stringstream ss;
  // ensure ifstream objects can throw exceptions:
  in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // open files
    in.open(path.c_str());
    // read file's buffer contents into streams
    ss << in.rdbuf();
    // close file handlers
    in.close();
  } catch (std::ifstream::failure e) {
    std::string error_message = "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ";
    error_message += "\nFile path: ";
    error_message += path;
    exit_program(error_message);
  }
  // convert stream into string
  return ss.str();
}



/* 
 * 
 * OPENGL FUNCTIONS
 * 
 * 
 * 
 * */

// initial opengl
void initial_glfw() {
  assert_true(glfwInit() == GLFW_TRUE, "glfw initial error");
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(
      GLFW_OPENGL_FORWARD_COMPAT,
      GL_TRUE);  // uncomment this statement to fix compilation on OS X
#endif
}

// initial glad
void initial_glad() {
  assert_true(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) != 0,
              "glad load errror");
}

// initial imgui
void initial_imgui(GLFWwindow* window) {
  // Setup ImGui binding
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard
  // Controls  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable
  // Gamepad Controls
  ImGui_ImplGlfwGL3_Init(window, true);

  // Setup style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

  // Load Fonts
  // - If no fonts are loaded, dear imgui will use the default font. You can
  // also load multiple fonts and use ImGui::PushFont()/PopFont() to select
  // them.
  // - AddFontFromFileTTF() will return the ImFont* so you can store it if you
  // need to select the font among multiple.
  // - If the file cannot be loaded, the function will return NULL. Please
  // handle those errors in your application (e.g. use an assertion, or display
  // an error and quit).
  // - The fonts will be rasterized at a given size (w/ oversampling) and stored
  // into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which
  // ImGui_ImplXXXX_NewFrame below will call.
  // - Read 'misc/fonts/README.txt' for more instructions and details.
  // - Remember that in C/C++ if you want to include a backslash \ in a string
  // literal you need to write a double backslash \\ !
  // io.Fonts->AddFontDefault();
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
  // ImFont* font =
  // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f,
  // NULL, io.Fonts->GetGlyphRangesJapanese());  IM_ASSERT(font != NULL);
}

// inital opengl
void initial_opengl(std::function<void(void)> set_window, GLFWwindow*& window) {
  initial_glfw();
  set_window();
  initial_glad();
  initial_imgui(window);
  glViewport(0, 0, 800, 600);
}

// set vao
void set_vao(GLuint& VAO, GLuint& VBO, GLuint& EBO,
             std::function<void(GLuint, GLuint, GLuint)> set_buffer,
             bool is_buffer_need_initial = true) {
  glGenVertexArrays(1, &VAO);
  if (is_buffer_need_initial) glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  set_buffer(VAO, VBO, EBO);
}

typedef PFNGLGETSHADERIVPROC CheckShaderHasErrorFunc;
typedef PFNGLGETSHADERINFOLOGPROC GetShaderErrorMessageFunc;

// check if shader works well
void check_shader_have_error(GLuint id, GLenum type,
                             CheckShaderHasErrorFunc check_has_error,
                             GetShaderErrorMessageFunc get_error_info) {
  GLint no_error;
  GLchar info_log[INFO_LOG_SIZE];
  check_has_error(id, type, &no_error);
  if (no_error) return;
  get_error_info(id, INFO_LOG_SIZE, NULL, info_log);
  exit_program(info_log);
}

// compile shader
GLuint compile_shader(GLenum type, std::string path) {
  GLuint shader = glCreateShader(type);
  std::string str = read_string_from_path(path);
  const GLchar* source = str.c_str();
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);
  check_shader_have_error(shader, GL_COMPILE_STATUS, glGetShaderiv,
                          glGetShaderInfoLog);
  return shader;
}

// compile vertex shader
GLuint compile_vertex_shader(std::string path) {
  return compile_shader(GL_VERTEX_SHADER, path);
}

// compile fragment shader
GLuint compile_fragment_shader(std::string path) {
  return compile_shader(GL_FRAGMENT_SHADER, path);
}

// create program and link shader
GLuint create_program_with_shader(GLuint vertex_shader,
                                  GLuint fragment_shader) {
  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  check_shader_have_error(program, GL_LINK_STATUS, glGetProgramiv,
                          glGetProgramInfoLog);
  return program;
}

// create program and link shader with file path
GLuint create_program_with_shader(std::string vertex_shader_path,
                                  std::string fragment_shader_path) {
  GLuint vertex_shader = compile_vertex_shader(vertex_shader_path);
  GLuint fragment_shader = compile_fragment_shader(fragment_shader_path);
  GLuint program = create_program_with_shader(vertex_shader, fragment_shader);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  return program;
}

// create texture with file path
void create_texture(GLuint & texture, std::string file_path) {
  // load and create a texture
  // -------------------------
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);  // all upcoming GL_TEXTURE_2D
                                          // operations now have effect on this
                                          // texture object
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT (default
                               // wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  // tell stb_image.h to flip loaded texture's on the y-axis.
  stbi_set_flip_vertically_on_load(false);
  // std::string str = read_string_from_path(file_path);
  unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &nrChannels, 0);
  assert_true(data, "Failed to load texture " + file_path);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
}
// set int
void set_shader_int(GLuint id, const std::string & name, int value) {
  glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
// set mat4
void set_shader_mat4(GLuint id, const std::string &name, const glm::mat4 &mat) {
  // std::cout << glm::to_string(mat) << std::endl;
  glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


}  // namespace helper

#endif