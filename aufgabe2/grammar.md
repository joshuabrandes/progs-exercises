# 2.1 Regex für folgende Ausdrücke

- Kommentare in Pascal: diese werden in (* und *) oder { und } eingeschlossen und dürfen beliebige Zeichen enthalten.

```regexp
\(\*.*\*\)|\{.*\}
```

- Numerische Integerkonstanten in C: diese können oktale, dezimale oder hexadezimale Werte sein. Oktale Integerwerte
  beginnen mit einer 0 und dürfen nur die Ziffern 0-7 enthalten. Hexadezimale Integerwerte beginnen mit 0x oder 0X und
  dürfen die Ziffern 0-9 und die Buchstaben a/A-f/F enthalten. Dezimale Integerwerte dürfen nicht mit 0 beginnen.
  Integerwerte können am Ende optional die Zeichen U oder u ("unsigned") und/oder L oder l ("long") oder LL oder ll ("
  long long") enthalten.
    - Dezimal: beginnt nicht mit 0
    - Oktal: beginnt mit 0 und enthält nur Ziffern 0-7
    - Hexadezimal: beginnt mit 0x oder 0X und enthält Ziffern 0-9 und Buchstaben a/A-f/F
    - Optional: U/u, L/l, LL/ll

```regexp
0[0-7]+([uU][lL]{1,2})? | 0[xX][0-9a-fA-F]+([uU][lL]{1,2})? | [1-9][0-9]*([uU][lL]{1,2})?
```

# 2.2 Grammatik I

```
S -> aSbS | bSaS | e
```

- a) zeige, dass Grammatik nicht eindeutig ist
    - siehe b)
    - S -> aSbS -> abS -> abaSbS -> ababS -> abab
    - *nicht eindeutig, da es mehrere Ableitungen gibt*
- b) rechtsableitung für abab
    - S -> aSbS -> aSbaSbS ->aSbaSb -> aSbab -> abab
- c) zeichnen sie den Ableitungsbaum für abab

```
    S
 /  |   |  \
a   S   b   S
    |      /  |  |  \
    e      a  S  b   S
              |      |
              e      e
```

# 2.3 Grammatik II (LUA Ableitungsbäume)

_siehe GoodNotes_

# 2.4 Grammatik III

```
S -> aSa | bB
B -> bB | e
```

recursive descent Parser für die Grammatik in [Python](./recursive_descent_parser.cs)

# 2.5 Grammatik IV

Grammatik:
```
IfStatement -> if ( Expression ) Statement | if ( Expression ) Statement else Statement
Statement -> Assignment | IfStatement | Block
Block -> { Statements }
Statements -> Statements Statement | Statement
```
Code:
```
if (x < 0)
  if (y < 0) y = y-1;
  else y = 0;
```
- Problem bei Parsen des Codefragments: 
  - else gehört zum ersten if-Statement, da es keine Klammern gibt
  - Lösung: Klammerung oder nach Einrückung parsen
