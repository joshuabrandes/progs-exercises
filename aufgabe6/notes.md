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
> Weiterhin soll für das Alignment gelten, dass alle primitiven Datentypen ihrer Größe entsprechend im Speicher
> ausgerichtet
> sein sollen (d.h. 'char' an vielfachen von 1-byte Adressen, 'short' an vielfachen von 2 usw.). Es handelt sich um eine
> 64-bit
> Architektur.

```csharp
| s | c | - | t |
| d | ------- |
| f |
| i | ---- |
```

- Berechnung der Größe des Structs: 4 8-Byte Blöcke = 32 Bytes
- Array mit 10 Elementen: (3,5 * 8-Byte Blöcke) * 10 = 280 Bytes
- optimale Anordnung:
    - Größe des Structs: 3 * 8-Byte Blöcke = 24 Bytes
    - Array mit 10 Elementen: 2,5 * 8-Byte Blöcke * 10 = 200 Bytes

```csharp
| s | c | d | t |
| f |
| i | ---- |
```

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
- Verwaltungsinformationen im Array `l:
    - Size: länge des Arrays (hier 3)
    - Type: Typ des Arrays gibt auch größe der Elemente an (hier B)
    - Alignment Padding: je nach Architektur, gibt an wie viele Bytes noch benötigt werden, damit das Array korrekt
      ausgerichtet ist
- Größe und Alignment der Zeichen in modernen Sprachen (wie C# oder Java):
    - `char` = 2 Bytes (UTF-16)
- C#: String kann null-Zeichen (`\0`) enthalten. Wie kann das Laufzeitsystem die Länge des Strings bestimmen?
    - `string` in C# ist ein immutable Objekt
    - Länge des Strings wird in einem separaten Feld gespeichert

## Aufgabe 5 - Structs und Arrays 4

```csharp
struct {
  short s;
  float f;
} array_of_structs[4][3];

struct {
  short s[4][3];
  float f[4][3];
} struct_of_arrays;
```

> Nehmen Sie an, dass der Datentyp short 2- und der Datentyp float 4-byte Speicher benötigt. Weiterhin sollen
die Datentypen 2- bzw. 4-byte-aligned sein und Strukturen weder gepackt noch umgeordnet werden dürfen (64-bit Architektur).

- Speicherlayout von `array_of_structs`:
  - `short` = 2 Bytes
  - `float` = 4 Bytes
  - Kein Padding, da `short` und `float` 2- bzw. 4-Byte-aligned sind
```csharp
| s | f | s2 |
| f2 | s3 | f3 |
…
```

- Speicherlayout von `struct_of_arrays`:
  - `short` = 2 Bytes
  - `float` = 4 Bytes
  - Padding für `short` und `float` nicht notwendig
```csharp
| s00 | s01 | s02 | s10 |
| s11 | s12 | s20 | s21 |
| s22 | s30 | s31 | s32 |
| f00 | f01 |
| f02 | f10 |
| f11 | f12 |
| f20 | f21 |
| f22 | f30 |
| f31 | f32 |
```

- Speicherbedarf von `array_of_structs`:
  - 4 * 3 * (2 + 4) = 72 Bytes
- Speicherbedarf von `struct_of_arrays`:
  - `short` Array: 4 * 3 * 2 = 24 Bytes
  - `float` Array: 4 * 3 * 4 = 48 Bytes
  - Insgesamt: 72 Bytes
- Formel für die Berechnung der Position von `array_of_structs[i][j].f`:
  - Basisadresse: F
  - Größe eines Elements: 2 + 4 = 6 Bytes
  - _**????**_
- Formel für die Berechnung der Position von `struct_of_arrays.f[i][j]`:
  - Basisadresse: F
  - Größe eines Elements: 4 Bytes
  - Position: F + 24 + 4 * (3 * i + j)
- Effizienz: Strukturen von Arrays oder Arrays von Strukturen?
  - Strukturen von Arrays sind effizienter, aus diversen Gründen:
    - Gleiche Datentypen sind zusammen im Speicher &rarr; besseres Alignment
    - VErarbeitung mehrerer Felder im Array ist effizienter (SIMD-Instruktionen für Vektoroperationen in modernen CPUs)
    - Bessere Cache-Performance durch Minimieren von Cache-Misses
