# Aufgabe 4 – Antworten

## 4.1
```js
function main() {
  var arr = new Array();

  for (var i = 0; i < 10; ++i) {
    var j=0;
    arr[i] = function() { j++; console.log(j); }
  }

  arr.forEach(function(a) { a(); });
}

main();
```
1. Closures: 
   1. `arr[i] = function() { j++; console.log(j); }` greift auf die Variable `j` zu, die in der äußeren Funktion `main` definiert ist. Die Funktionen in `arr` sind Closures, da sie auf die Variable `j` zugreifen, die in einem anderen Scope definiert ist.
   2. Die Funktionen in `arr` haben alle Zugriff auf die gleiche Variable `j`, da sie alle auf die gleiche Variable `j` in `main` zugreifen.
2. Stack und Heap in Zeile 8:
   1. Der Stack enthält die Variable `i`, die in der Schleife definiert ist. (Wird bei jedem Schleifendurchlauf neu erzeugt und am Ende des Schleifendurchlaufs wieder gelöscht.)
   2. Der Heap enthält die Funktionen, die in `arr` gespeichert sind. Außerdem enthält der Heap die Variable `j`, auf die die Funktionen in `arr` zugreifen.
3. Ausgaben:
   1. JavaScript: 1 bis 10
   2. C++: 10 mal 1
   3. Python: 1 bis 10
