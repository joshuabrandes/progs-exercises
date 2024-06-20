# Lösungen
## Aufgabe 1

- Das [Programm](./a5_1.cpp) soll zwei zahlen addieren.
- `x` hat den Typ `Integer`
- `f` ist eine Funktion, die eine Zahl, mit der bei der Definition von `f` übergebenen Zahl addiert
  - `std::function<int(int)> f = [x](int y) { return x + y; };`

## Aufgabe 2

- Das [Programm](./a5_2.cpp) 
- `bar()` überschreibt dangling reference von `foo()` mit Wert `2`
  - ausgabe ist `42` (Zuweisung im Stack in `bar()`)

## Aufgabe 3

- Das [Programm](./a5_3.cpp)
- s. Lösung

## Aufgabe 4

- Das [Programm](./a5_4.cpp) kompiliert nicht, da `Foo x();` als Funktionsdeklaration interpretiert wird
  - `Foo x;` ist die richtige Schreibweise

## Aufgabe 5

- Das [Programm](./a5_5.cpp) scheitert in macOS mit ninja als Buildsystem mit Ausgabe `Process finished with exit code 134 (interrupted by signal 6:SIGABRT)`
- das liegt daran, dass im Array ein zuweisung an den Index `-1` stattfindet und macOS bei Zugriff auf einen Index außerhalb des dem Programm zugewiesenen Speicherbereichs einen Abort Kommando ausführt


## Aufgabe 6

```js
    function sumit(a, first, n) {
      var sum = 0;
      var i;
      for (i = first; i < first+n; i++) {
        sum += a[i];
      }
      return sum;
    }

    var f = sumit([ 1, 2, 3, 4 ], 1, '3');

    console.log(f);
```

- scheitert, weil `string` Typ gewinnt und bei der Addition `first+n` `first` (`1`) und `'3'` konkateniert werden

## Aufgabe 7

- JS-Objekte kennen die Methoden `toString()` und `valueOf()`
- `toString()` manchmal ist `valueOf()` nicht definiert, dann wird `toString()` verwendet
  - casting zu `string` ist immer möglich und führt oft zu Problemen
