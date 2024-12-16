cmake_minimum_required(VERSION 3.29)
project(new)

# Chemins vers les fichiers SDL2
set(SDL2_INCLUDE_DIR "../new/SDL2-2.30.9/x86_64-w64-mingw32/include/SDL2")
set(SDL2_LIB_DIR "../new/SDL2-2.30.9/x86_64-w64-mingw32/lib")

# Inclure les dossiers nécessaires
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

# Ajouter les fichiers source de votre projet
add_executable(new main.c)

# Lier SDL2 au projet
target_link_libraries(new SDL2 SDL2main SDL2_image SDL2_ttf)