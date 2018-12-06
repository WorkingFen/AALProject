# Problem grafowy

Wszelkie informacje na temat projektu można znaleźć w [**dokumentacji**](https://github.com/WorkingFen/AALProject/blob/master/Dokumentacja.pdf) 

## Pierwsze kroki
Zanim zaczniemy cokolwiek pobierać, to najpierw muszę cokolwiek zrobić.

### Wymagania wstępne

1. Pobranie [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/)
   - Należy pobrać wersję odpowiednią dla swojego kompilatora oraz typu systemu operacyjnego.
2. Pobranie wszystkich plików, które znajdują się w [tym](https://github.com/WorkingFen/AALProject/tree/master/Masts) repozytorium

### Instalacja
##### Instalacja biblioteki SFML dla Code::Blocks

1. Pobierz bibilioteki SFML
2. Wprowadź je do katalogu, do ścieżki którego masz łatwy dostęp
3. Utwórz nowy projekt Code::Blocks
4. Pobierz wszystkie pliki z tego repozytorium i wprowadź je do projektu
5. Przejdź do **_Build Options_** projektu
6. Naciśnij nazwę projektu i przejdź do **_Linker settings_**
7. Wprowadź w pole **_Other linker options_**:
   
   ```
   -static
   -static-libgcc
   ```
   
8. Przejdź do **_Search directories_** i w zakładce **_Compiler_** wprowadź ścieżkę do pobranych bibliotek SFML z postfiksem **\include**
9. W zakładce **_Linker_** wprowadź ścieżkę do pobranych bibliotek SFML z postfiksem **\lib**
10. Przejdź do sekcji **_Debug_**, gdzie w zakładce **_Compiler settings/Compiler Flags_**, trzeba zaznaczyć flagę **-std=c++11**
11. Przejdź do zakładki **_Linker settings_**
12. Wprowadź w pole **_Link libraries_**:

   ```
   sfml-audio-d
   sfml-graphics-d
   sfml-main-d 
   sfml-network-d 
   sfml-system-d 
   sfml-window-d
   ```
  
13. Przejdź do sekcji **_Release_**, gdzie w zakładce **_Compiler settings/Compiler Flags_**, trzeba zaznaczyć flagę **-std=c++11**
14. Przejdź do zakładki **_Linker settings_**
15. Wprowadź w pole **_Link libraries_**:

   ```
   sfml-audio
   sfml-graphics
   sfml-main
   sfml-network
   sfml-system
   sfml-window
   ```
   
16. Wprowadź w pole **_Other linker options_**:

   ```
   -static
   -static-libgcc
   -static-libstdc++
   ```
   
17. Zapisz wprowadzone zmiany
18. Do katalogu gdzie znajdują się pliki projektu należy dodać wszystkie biblioteki dynamiczne z katalogu **\bin** SFMLa
   
 
## Technologie
Biblioteka graficzna - [SFML](https://www.sfml-dev.org/)

## Autor
- **Zawadka Piotr** - [WorkingFen](https://github.com/WorkingFen)

## Licencja
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
