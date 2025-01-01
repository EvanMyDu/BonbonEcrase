cmake_minimum_required(VERSION 3.29)
project(new)

# Chemins vers les fichiers SDL2
set(SDL2_INCLUDE_DIR "../new/SDL2-2.30.9/x86_64-w64-mingw32/include/SDL2")
set(SDL2_LIB_DIR "../new/SDL2-2.30.9/x86_64-w64-mingw32/lib")

# Inclure les dossiers nécessaires
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

set(INCLUDES header/ImageHandler.h header/Game.h header/AfficheFenetre.h header/Button.h header/score.h)
set(SOURCES src/ImageHandler.c src/Game.c src/AfficheFenetre.c src/Button.c src/score.c)
# Ajouter les fichiers source de votre projet
add_executable(bonbon_ecrase main.c ${INCLUDES} ${SOURCES})

# Lier SDL2 au projet
target_link_libraries(bonbon_ecrase SDL2 SDL2main SDL2_image SDL2_ttf)