# Lösungen
## Aufgabe 1

- Das [Programm](./a5_1.cpp) soll zwei zahlen addieren.
- `x` hat den Typ `Integer`
- `f` ist eine Funktion, die eine Zahl, mit der bei der Definition von `f` übergebenen Zahl addiert
  - `std::function<int(int)> f = [x](int y) { return x + y; };`