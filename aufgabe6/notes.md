## Aufgabe 1 - Typinferenz

- Programm kompiliert nicht, da der Typ für den Mix aus `Shape` und `RoundShape` nicht eindeutig ist. Die Typinferenz
  ist `object` und nicht `Shape`.
    - Lösungen:
        - Casten
        - Vererbungsstruktur
- statischer Typ in ArrayList `al`: `Shape` und `RoundShape`
- dynamischer Typ in ArrayList `al`: `object`
- Typ in Zeile 25: `object?` (nullable)
- In Zeile 30 wird versucht das Element in `al` zu casten nach `Shape`. Daher kann darauf dann `draw()` aufgerufen
  werden.

## Aufgabe 2 - Structs udn Arrays 1

```csharp
struct A {
  short s;
  char c;
  int t;
  char d;
  double f;
  int i;
};
```

> Es sollen folgende Größen für Datentypen gelten: 'char' 1-byte, 'short' 2-bytes, 'double' 8-bytes, 'int' 4-bytes.
Weiterhin soll für das Alignment gelten, dass alle primitiven Datentypen ihrer Größe entsprechend im Speicher ausgerichtet
sein sollen (d.h. 'char' an vielfachen von 1-byte Adressen, 'short' an vielfachen von 2 usw.). Es handelt sich um eine 64-bit
Architektur.

| s | c | - | t | <br>
| d | ------- | <br>
| f | <br>
| i | ---- |

- Berechnung der Größe des Structs: 4 8-Byte Blöcke = 32 Bytes
- Array mit 10 Elementen: (3,5 * 8-Byte Blöcke) * 10 = 280 Bytes
- optimale Anordnung:
  - Größe des Structs: 3 * 8-Byte Blöcke = 24 Bytes
  - Array mit 10 Elementen: 2,5 * 8-Byte Blöcke * 10 = 200 Bytes

| s | c | d | t | <br>
| f | <br>
| i | ---- |

## Aufgabe 3 - Structs und Arrays 2

```csharp
struct {
  int n;
  char c;
} A[10][10];
```

- Größe des Structs: 5 Bytes &rarr; belegt 8 Bytes
  - Adresse += 8 bei 64-Bit-Architektur
- `A[0][0]` soll Adresse 1000 haben
- Adresse von `A[3][7]` berechnen
  - `A[0][0]` = 1000
  - `A[3][0]` = 1000 + 3 * 10 * 8 = 1240
  - `A[3][7]` = 1240 + 7 * 8 = 1296

## Aufgabe 4 - Structs und Arrays 3

```csharp
namespace Aufgabe9 {

  struct A {
    public string str;
    public short s;
  }

  struct B {
    public int  a;
    public bool b;
    public A    c;
  }

  class Program {

    public static void foo() {
        int    i = 2;
        double j = 1.0;

        B k;
        k.a     = 1;
        k.b     = true;
        k.c.str = "Hi";
        k.c.s   = 255;

        B[] l = new B[3];
        l[0] = k;
        l[1] = l[0];
        l[2] = l[1];
        /* a) */
    }

    public static void Main(string[] args) {
        foo();
    }
  }
}
```

- Stackframe bei *a)*:
```csharp
// Stackframe von foo:
+----------------------+ 
| i    (int)      2    | // 4 bytes
+----------------------+
| j    (double)   1.0  | // 8 bytes
+----------------------+
| k.a  (int)      1    | // 4 bytes
| k.b  (bool)     true | // 1 byte
|        (padding)     | // 3 bytes (Padding for alignment)
| k.c.str  (ref) "Hi"  | // 8 bytes (reference to string)
| k.c.s   (short)  255 | // 2 bytes
|        (padding)     | // 6 bytes (Padding for alignment)
+----------------------+
| l[0].a        = 1    | // 4 bytes
| l[0].b        = true | // 1 byte
|        (padding)     | // 3 bytes (Padding for alignment)
| l[0].c.str    = "Hi" | // 8 bytes (reference to string)
| l[0].c.s      = 255  | // 2 bytes
|        (padding)     | // 6 bytes (Padding for alignment)
+----------------------+
| l[1] (ref to l[0])   | // 24 bytes (struct B size)
+----------------------+
| l[2] (ref to l[1])   | // 24 bytes (struct B size)
+----------------------+
| l    (array ref)     | // 8 bytes (reference to array)
+----------------------+
```

- Wert von `k.b` muss relativ zum Stackframe berechnet werden
  - `i` = 4 Bytes
  - `j` = 8 Bytes
  - `k.a` = 4 Bytes
  - 4 + 8 + 4 = 16 Bytes &rarr; Adresse von `k.b` = F + 16
- Adresse von `l[2].c.str`:
  - i (4 bytes)
  - j (8 bytes)
  - k (24 bytes)
  - l[0] (24 bytes)
  - l[1] (24 bytes)
  - l[2] (24 bytes)
  - 4 + 8 + 24 + 24 + 24 + 24 = 108 Bytes &rarr; Adresse von `l[2].c.str` = F + 108
- 
