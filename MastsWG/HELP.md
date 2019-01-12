# Pomoc dla projektu MastsWG

Program jest niegraficznym odpowiednikiem programu Masts. 
Wszystkie pliki, które mogą być rozwiązane powinny znajdować się w katalogu Resources i powinny być plikami o rozszerzeniu .txt. 

Program rozpoczyna działanie po odpaleniu przez terminal i posiada  składnię:

```
./Masts.exe [filename] [amount|NONE] [...]
```

Gdzie:
- **filename** jest nazwą pliku bez rozszerzenia, z którego chcemy odczytać problem.
- **amount** jest ilością iteracji wykonania problemu (dla lepszego pokazania czasu wykonywania)
  ```
  Nie trzeba wpisywać, automatycznie będzie przypisana 1 iteracja.
  
  ```
  
- reszta argumentów zostanie zignorowana

# Działanie programu

Program przyjmuje na wejście plik z danymi, a następnie wykonując operacje określone przez odczytany algorytm, wypisuje dane:
- Plik, którego dane zostały przetworzone;
- Algorytm użyty do znalezienia odpowiedzi;
- Ilość masztów, które należało sprawdzić;
- Odległość od najdalej położonych masztów względem sumy odległości (pokazanie, że wynik jest w okolicach połowy sumy odległości)
- Pierwszy maszt, na którym powinien się pojawić radar
- Drugi maszt, na którym powinien się pojawić radar
- Czas, który potrzebny był do znalezienia masztów;

# Rozwiązywanie problemów

Wszelkie problemy, które powodują, że program jest niezdolny do działania, powinny zakończyć się ponownym uruchomieniem programu.

W razie błędów, proszę poinformować autora, dziękuję.