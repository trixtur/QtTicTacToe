# Qt Tic Tac Toe

A two-player Tic Tac Toe game written in C++ and Qt.

Use the Edit menu to choose Two Players or play as X against the Easy, Medium,
or Impossible computer opponent. Easy plays randomly, Medium takes immediate
wins and blocks but otherwise plays randomly, and Impossible uses perfect play.

## Build and run

```sh
qmake6 TicTacToe.pro
make
./TicTacToe.app/Contents/MacOS/TicTacToe
```

## Tests

The rules are isolated in `Game`, which can be tested without a display server:

```sh
qmake6 tests/tictactoe_test.pro
make
./tictactoe_test.app/Contents/MacOS/tictactoe_test
```

The application emits structured Qt logging under the `tictactoe.game` category. Enable it selectively with:

```sh
QT_LOGGING_RULES='tictactoe.game.debug=true' ./TicTacToe.app/Contents/MacOS/TicTacToe
```
