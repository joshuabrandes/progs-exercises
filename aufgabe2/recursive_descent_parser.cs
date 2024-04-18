enum Token { a, b, EndOfFile }
class abbaParser {
//... main
// Get lookahead
Token LookAhead { get => scanner.Current; }
// Check and consume lookahead
void matchToken(Token token) {
  if (LookAhead == token)
    scanner.MoveNext();
  else
    throw new Exception();
}
//S -> aSa | B (müsste bB sein)
public void parseS() {
  switch (LookAhead) {
  case Token.a:
    matchToken(Token.a);
    parseS();
    matchToken(Token.a);
    break;
  case Token.b:
    parseB();
    break;
  case Token.EndOfFile:
    break;
  default:
    throw new Exception();
  }
}
//TODO: B -> bB |  e
public void parseB() {
    switch (LookAhead) {
    case Token.b:
      matchToken(Token.b);
      parseB();
      break;
    }
    case Token.EndOfFile:
      break;
}
