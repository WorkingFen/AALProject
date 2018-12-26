# Pomoc dla projektu Generator

Celem programu jest generowanie problemów, które będą rozwiązywane przy pomocy programu Masts.
Wszystkie wygenerowane pliki znajdują się w katalogu Out i są plikami o rozszerzeniu .txt.
W celu rozwiązania wygenerowanego problemu, należy skopiować/przenieść plik do Resources w katalogu programu Masts, a następnie odpalić program. 

Program działa przy pomocy terminala.
Aby wygenerować problem, należy wywołać program w taki sposób:

```
./Generator.exe [filename] [algorithm|NONE] [amountOfVertices|NONE]
```

Gdzie:
- **filename** jest nazwą pliku bez rozszerzenia, do którego chcemy zapisać problem (nazwa powinna się składać ze znaków alfanumerycznych, bez znaków specjalnych, a spacja powinna być zastąpiona przez '_').
- **algorithm** jest odpowiednią nazwą algorytmu pisaną WIELKIMI literami, za pomocą którego chcemy dany problem rozwiązać.
  ```
  Nie trzeba wpisywać, automatycznie będzie przypisany algorytm LINEAR.
  W przypadku chęci wpisania liczby wierzchołków, ten argument nie może pozostać pusty.
  
  ```
  
- **amountOfVertices** jest liczbą wierzchołków, z której ma być stworzony graf problemu.
  ```
  Nie trzeba wpisywać, automatycznie będzie przypisane 20 wierzchołków.
  
  ```

# Problemy i rozwiązania

## Too little arguments or too many arguments

Odpowiedni sposób wywoływania programu:

```
./Generator.exe [filename] [algorithm|NONE] [amountOfVertices|NONE]
```

## Wrong type of algorithm

Są trzy algorytmy, które można używać:

- BRUTE
- MASTS
- LINEAR

**Ich nazwy należy wpisywać wielkimi literami!**

## Wrong amount of vertices

Powinno być więcej niż jeden wierzchołek. W przeciwnym wypadku taki graf i zadanie nie mają sensu. W OGÓLE 