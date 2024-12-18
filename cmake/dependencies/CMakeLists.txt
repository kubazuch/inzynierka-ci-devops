include(FetchContent)
set(CMAKE_EXPORT_COMPILE_COMMANDS
    OFF
    CACHE BOOL "Do not generate compile commands database for dependencies"
          FORCE)

# ##############################################################################
# GLAD
# ##############################################################################
message(CHECK_START "Fetching GLAD")
list(APPEND CMAKE_MESSAGE_INDENT "  ")

FetchContent_Declare(
  glad
  GIT_REPOSITORY "https://github.com/Dav1dde/glad.git"
  GIT_TAG "v2.0.7"
  PATCH_COMMAND git apply --ignore-whitespace
                "${CMAKE_CURRENT_LIST_DIR}/../../patches/glad.patch"
  UPDATE_DISCONNECTED 1)
FetchContent_MakeAvailable(glad)
FetchContent_GetProperties(glad)

add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
glad_add_library(
  glad
  STATIC
  REPRODUCIBLE
  EXCLUDE_FROM_ALL
  LOADER
  API
  gl:core=4.6)

list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "fetched")

# ##############################################################################
# GLFW
# ##############################################################################
if(BUILD_GLFW)
  message(CHECK_START "Fetching GLFW")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")

  set(GLFW_BUILD_EXAMPLES
      OFF
      CACHE BOOL "Do not build GLFW example programs" FORCE)
  set(GLFW_BUILD_TESTS
      OFF
      CACHE BOOL "Do not build GLFW test programs" FORCE)
  set(GLFW_BUILD_DOCS
      OFF
      CACHE BOOL "Do not build GLFW documentation" FORCE)
  set(GLFW_INSTALL
      OFF
      CACHE BOOL "Do not install the GLFW" FORCE)

  FetchContent_Declare(
    glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.4"
    PATCH_COMMAND git apply --ignore-whitespace
                  "${CMAKE_CURRENT_LIST_DIR}/../../patches/glfw.patch"
    UPDATE_DISCONNECTED 1)
  FetchContent_MakeAvailable(glfw)

  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

# ##############################################################################
# IMGUI
# ##############################################################################
message(CHECK_START "Fetching ImGui")
list(APPEND CMAKE_MESSAGE_INDENT "  ")

FetchContent_Declare(
  imgui
  GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
  GIT_TAG "v1.91.1-docking"
  PATCH_COMMAND git apply --ignore-whitespace
                "${CMAKE_CURRENT_LIST_DIR}/../../patches/imgui.patch"
  UPDATE_DISCONNECTED 1)
FetchContent_MakeAvailable(imgui)

list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "fetched")

# ##############################################################################
# GLM
# ##############################################################################
if(BUILD_GLM)
  message(CHECK_START "Fetching GLM")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")

  FetchContent_Declare(
    glm
    GIT_REPOSITORY "https://github.com/g-truc/glm.git"
    GIT_TAG "1.0.1"
    PATCH_COMMAND git apply --ignore-whitespace
                  "${CMAKE_CURRENT_LIST_DIR}/../../patches/glm.patch"
    UPDATE_DISCONNECTED 1)
  FetchContent_MakeAvailable(glm)

  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()

# ##############################################################################
# GTest
# ##############################################################################
if(BUILD_TESTING)
  message(CHECK_START "Fetching GoogleTest")
  list(APPEND CMAKE_MESSAGE_INDENT "  ")

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "v1.15.2"
  )

  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  list(POP_BACK CMAKE_MESSAGE_INDENT)
  message(CHECK_PASS "fetched")
endif()
