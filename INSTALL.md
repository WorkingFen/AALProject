# Problem masztów - instalacja

## Instalacja biblioteki SFML dla Code::Blocks 

Wymagane do projektu [Masts]()

1. Wprowadź pobrane biblioteki SFML do katalogu, do ścieżki którego masz łatwy dostęp
2. Utwórz nowy projekt Code::Blocks i [wprowadź pliki z repozytorium](#wprowadzanie-plików-do-projektu-codeblocks)
3. Przejdź do **_Build Options_** projektu
4. Naciśnij nazwę projektu i przejdź do **_Linker settings_**
5. Wprowadź w pole **_Other linker options_**:
   
   ```
   -static
   -static-libgcc
   ```
   
6. Przejdź do **_Search directories_** i w zakładce **_Compiler_** wprowadź ścieżkę do pobranych bibliotek SFML z postfiksem **\include**
7. W zakładce **_Linker_** wprowadź ścieżkę do pobranych bibliotek SFML z postfiksem **\lib**
8. Przejdź do sekcji **_Debug_**, gdzie w zakładce **_Compiler settings/Compiler Flags_**, trzeba zaznaczyć flagę **-std=c++11**
9. Przejdź do zakładki **_Linker settings_**
10. Wprowadź w pole **_Link libraries_**:

    ```
    sfml-audio-d
    sfml-graphics-d
    sfml-main-d 
    sfml-network-d 
    sfml-system-d 
    sfml-window-d
    ```
  
11. Przejdź do sekcji **_Release_**, gdzie w zakładce **_Compiler settings/Compiler Flags_**, trzeba zaznaczyć flagę **-std=c++11**
12. Przejdź do zakładki **_Linker settings_**
13. Wprowadź w pole **_Link libraries_**:

    ```
    sfml-audio
    sfml-graphics
    sfml-main
    sfml-network
    sfml-system
    sfml-window
    ```
   
14. Wprowadź w pole **_Other linker options_**:

    ```
    -static
    -static-libgcc
    -static-libstdc++
    ```
   
15. Zapisz wprowadzone zmiany
16. Dodaj wszystkie biblioteki dynamiczne z katalogu **\bin** SFMLa do katalogu gdzie znajdują się pliki projektu 

## Wprowadzanie plików do projektu Code::Blocks

1. Dodaj pobrane pliki repozytorium do katalogu z plikami projektu
2. Naciśnij PPM na nazwę projektu
3. Wybierz opcję **_Add files_**
4. Wybierz pliki, które chcesz dodać do projektu
5. Zatwierdź wybór
6. Przejdź do **_Build Options_** projektu
7. Zaznacz w **_Compiler Flags_** flagę **-std=c++11**