# Pomoc dla projektu Masts

Celem programu jest rozwiązywanie problemów, które były wygenerowane przy pomocy programu Generator lub stworzone przez użytkownika, w sposób analogiczny do pliku przykładowego.
Wszystkie pliki, które mogą być rozwiązane powinny znajdować się w katalogu Resources i powinny być plikami o rozszerzeniu .txt. 

Program rozpoczyna działanie po odpaleniu przez terminal, bądź po odpaleniu pliku .exe

Program odpalany przez terminal ma składnię:

```
./Masts.exe [filename|NONE] [amount|NONE] [...]
```

Gdzie:
- **filename** jest nazwą pliku bez rozszerzenia, z którego chcemy odczytać problem.
  ```
  Nie trzeba wpisywać, automatycznie zostanie odpalony program okienkowy, w którym będzie można wpisać żądaną nazwę problemu.
  Po wywołaniu programu, należy nacisnąć **Enter** w celu rozpoczęcia jego działania.
  W przypadku chęci wpisania liczby iteracji, ten argument nie może pozostać pusty.
  
  ```
  
- **amount** jest ilością iteracji wykonania problemu (dla lepszego pokazania czasu wykonywania)
  ```
  Nie trzeba wpisywać, automatycznie będzie przypisana 1 iteracja.
  
  ```
   
- reszta argumentów zostanie zignorowana

# Działanie programu okienkowego

Program okienkowy przyjmuje na wejście wszystkie naciśnięcia klawiszy alfanumerycznych, co skutkuje wprowadzeniem żądanego znaku do nazwy pliku.
Naciśnięcie spacji skutkuje wprowadzeniem znaku '_', a klawisz Backspace kasuje ostatni wprowadzony znak.
Naciśnięcie Entera uruchamia program dla wcześniej wpisanej nazwy pliku.

# Rozwiązywanie problemów

Wszelkie problemy, które powodują, że program jest niezdolny do działania, powinny zakończyć się ponownym uruchomieniem programu.

W razie błędów, proszę poinformować autora, dziękuję.