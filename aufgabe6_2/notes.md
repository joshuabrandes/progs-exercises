## Aufgabe 6.6 - Smart-Pointer in C++

- Zeilennummern wo Compilerfehler auftreten:
  - 10: cast von `weak_ptr` zu `shared_ptr` ist nicht möglich
  - 18: `unique_ptr` kann nicht kopiert werden
- Erwartete Ausgabe:
  - 0235
  - Tatsächliche Ausgabe: 0200

---

ChatGPT:

Gerne erkläre ich dir, warum die Ausgabe des Programms "0200" ist.

### Analyse des Programmschritts für Schritt

```cpp
#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {

    std::shared_ptr<int> s1(new int(2));
    std::shared_ptr<int> s2;
    std::unique_ptr<int> u1(new int(3));
    std::weak_ptr<int>   w1;

    {
        std::shared_ptr<int> s4(s1);
        s2 = s4;
        std::unique_ptr<int> u2(std::move(u1));
        std::shared_ptr<int> s5(new int(5));
        w1 = s5;
        /**/
    }

    s1.reset();
    std::shared_ptr<int> s6 = w1.lock();

    std::cout << (s1 != nullptr ? *s1 : 0) << std::endl; // 0
    std::cout << (s2 != nullptr ? *s2 : 0) << std::endl; // 2
    std::cout << (u1 != nullptr ? *u1 : 0) << std::endl; // 0
    std::cout << (s6 != nullptr ? *s6 : 0) << std::endl; // 0
    return 0;
}
```

### Erklärung der Ausgabe

1. **Initialisierung:**
    ```cpp
    std::shared_ptr<int> s1(new int(2));
    std::shared_ptr<int> s2;
    std::unique_ptr<int> u1(new int(3));
    std::weak_ptr<int> w1;
    ```

  - `s1` ist ein `shared_ptr`, der auf einen `int`-Wert `2` zeigt.
  - `s2` ist ein leerer `shared_ptr`.
  - `u1` ist ein `unique_ptr`, der auf einen `int`-Wert `3` zeigt.
  - `w1` ist ein leerer `weak_ptr`.

2. **Innerer Block:**
    ```cpp
    {
        std::shared_ptr<int> s4(s1);
        s2 = s4;
        std::unique_ptr<int> u2(std::move(u1));
        std::shared_ptr<int> s5(new int(5));
        w1 = s5;
        /**/
    }
    ```

  - `s4` ist ein `shared_ptr`, der eine Kopie von `s1` ist, zeigt also auch auf `2`.
  - `s2` wird auf `s4` gesetzt, zeigt also auch auf `2`.
  - `u2` übernimmt den Besitz von `u1`, wodurch `u1` null wird und `u2` auf `3` zeigt.
  - `s5` ist ein `shared_ptr`, der auf `5` zeigt.
  - `w1` wird auf `s5` gesetzt, zeigt also auf `5`.

   Am Ende des Blocks werden `s4`, `u2` und `s5` zerstört. Die `shared_ptr` haben ihren Besitz erhöht, so dass `s2` weiterhin auf `2` zeigt. Der `weak_ptr` `w1` verweist auf `5`, aber `s5` wird zerstört, sodass der Wert nicht mehr existiert.

3. **Nach dem Block:**
    ```cpp
    s1.reset();
    std::shared_ptr<int> s6 = w1.lock();
    ```

  - `s1.reset()` setzt `s1` auf `nullptr`.
  - `w1.lock()` gibt einen leeren `shared_ptr` zurück, weil das Objekt, auf das `w1` zeigt, bereits zerstört wurde.

4. **Ausgabe:**
    ```cpp
    std::cout << (s1 != nullptr ? *s1 : 0) << std::endl; // 0
    std::cout << (s2 != nullptr ? *s2 : 0) << std::endl; // 2
    std::cout << (u1 != nullptr ? *u1 : 0) << std::endl; // 0
    std::cout << (s6 != nullptr ? *s6 : 0) << std::endl; // 0
    ```

  - `s1` ist `nullptr`, daher wird `0` ausgegeben.
  - `s2` ist nicht `nullptr`, es zeigt auf `2`, daher wird `2` ausgegeben.
  - `u1` ist `nullptr`, daher wird `0` ausgegeben.
  - `s6` ist `nullptr`, weil `w1` auf ein zerstörtes Objekt verweist, daher wird `0` ausgegeben.

Zusammengefasst ergibt das die Ausgabe: `0 2 0 0`.

---

- Heap und Stack zum Zeitpunkt bei `/**/`:

```cpp
Stack:
+-----------------------+
| argc                  | // Argument Count
+-----------------------+
| argv                  | // Argument Values
+-----------------------+
| s1 (shared_ptr<int>)  | --> Heap (int: 2)
+-----------------------+
| s2 (shared_ptr<int>)  | nullptr
+-----------------------+
| u1 (unique_ptr<int>)  | --> nullptr (moved to u2)
+-----------------------+
| w1 (weak_ptr<int>)    | --> s5 (int: 5)
+-----------------------+
| s4 (shared_ptr<int>)  | --> Heap (int: 2)
+-----------------------+
| u2 (unique_ptr<int>)  | --> Heap (int: 3)
+-----------------------+
| s5 (shared_ptr<int>)  | --> Heap (int: 5)
+-----------------------+
|                       |
|       ...             | // Other local variables or padding
|                       |
+-----------------------+
  
Heap:
+-------------------------------+
| int: 2 (referenced by s1, s4) |
+-------------------------------+
| int: 3 (referenced by u2)     |
+-------------------------------+
| int: 5 (referenced by s5, w1) |
+-------------------------------+
```

- Warum war der `std::auto_ptr`, der bis C++11 existierte, problematisch?
  - Kopierverhalten: transfer of ownership (nicht sicher)
    - ursprünglicher `auto_ptr` verliert Besitz und zeigt auf `nullptr`
      - nicht intuitiv und führt zu Fehlern
  - Nicht kompatibel mit Containern:
    - Standardlibrary-Container wie `std::vector` und `std::list` benötigen die Möglichkeit kopiert zu werden, ohne den Besitz zu übertragen
    - _Beispiel: s. unten_
  - `auto_ptr` hat keine move-Semantik
    - die mit C++11 eingeführten Smart-Pointer (`unique_ptr`, `shared_ptr`, `weak_ptr`) haben move-Semantik, diese ist in `auto_ptr` nicht implementiert
    - `auto_ptr` wird in der Regel mit `unique_ptr` ersetzt

```cpp
std::vector<std::auto_ptr<int>> vec;
std::auto_ptr<int> p(new int(10));

vec.push_back(p); // p überträgt den Besitz an das Container-Element
// p ist jetzt nullptr
```
