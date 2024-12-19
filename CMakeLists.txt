cmake_minimum_required(VERSION 3.10)
project(projet-informatique-sa7)

set(CMAKE_CXX_STANDARD 17)

# Enable automatic MOC, UIC, and RCC handling by CMake
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS frontend/ui)


# Find required Qt components
find_package(Qt6 COMPONENTS Widgets Multimedia REQUIRED)
find_package(Threads REQUIRED)

# Include directories

# Define shared source files for main and test executables
set(BACK_INCLUDE
    backend/include/Acheteur.h
    backend/include/back_end_main.h
    backend/include/BoiteAuLettres.h
    backend/include/Message.h
    backend/include/Produit.h
    backend/include/Protocol.h
    backend/include/Threads_var.h
    backend/include/Vendeur.h
    backend/include/Voiture.h
)

set(FRONT_INCLUDE
    frontend/include/chats.h
    frontend/include/garage.h
    frontend/include/MainWindow.h
    frontend/include/Parametres.h
    frontend/include/StartScreen.h
    frontend/include/store.h
    frontend/include/Vente.h
)

set(BACK_SRC
    backend/src/Acheteur.cpp
    backend/src/back_end_main.cpp
    backend/src/BoiteAuLettres.cpp
    backend/src/Message.cpp
    backend/src/Produit.cpp
    backend/src/Protocol.cpp
    backend/src/Threads_var.cpp
    backend/src/Vendeur.cpp
    backend/src/Voiture.cpp
)

set(FRONT_SRC
    frontend/src/chats.cpp
    frontend/src/garage.cpp
    frontend/src/MainWindow.cpp
    frontend/src/Parametres.cpp
    frontend/src/StartScreen.cpp
    frontend/src/store.cpp
    frontend/src/Vente.cpp
)

# Define UI files that require UIC generation
set(UI_FILES
    frontend/ui/MainWindow.ui
    frontend/ui/Parametres.ui
    frontend/ui/garage.ui
    frontend/ui/chats.ui
    frontend/ui/store.ui
    frontend/ui/StartScreen.ui
)




# Main application executable
add_executable(projet-informatique-sa7
    main.cpp
    ${FRONT_INCLUDE}
    ${FRONT_SRC}
    ${BACK_INCLUDE}
    ${BACK_SRC}
)
target_include_directories(projet-informatique-sa7 PRIVATE backend/include frontend/include)




# Link main executable against Qt Widgets and Multimedia libraries
target_link_libraries(projet-informatique-sa7 PRIVATE Qt6::Widgets Qt6::Multimedia pthread)
