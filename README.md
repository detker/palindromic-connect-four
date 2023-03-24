# palindromic-connect-four
my C implementation of connect-four game in "palindromic mode"

## specification (in polish lang):
Palindrom to wariant gry znanej jako Connect Four.

Gra jest rozgrywana przez dwóch graczy, nazywanych Pierwszym i Drugim, na prostokątnej planszy, ustawionej pionowo, podzielonej na wiersze i kolumny. Każdy gracz ma swój rodzaj piona.

Na początku gry plansza jest pusta. Zaczyna gracz Pierwszy.

Gracze, na przemian, wykonują ruch, kładąc swój pion na polu planszy. Pion jest umieszczany w wybranej przez gracza kolumnie, w jej pierwszym wolnym polu, licząc od dołu planszy.

Gracz wygrywa, jeśli swoim ruchem zbudował z pionów na kolejnych polach tego samego wiersza, kolumny lub przekątnej palindrom określonej długości.

Gra jest parametryzowana trzema dodatnimi liczbami całkowitymi:

<ul>
<li>WIERSZE to liczba wierszy planszy,</li>
<li>KOLUMNY to liczba kolumn planszy,</li>
<li>DLUGOSC to długość budowanego palindromu.</li>
</ul>

Wartości parametrów gry WIERSZE, KOLUMNY i DLUGOSC są określone za pomocą stałych symbolicznych, które można zdefiniować opcją -D kompilatora.

W kodzie programu są podane wartości domyślne tych stałych:
<ul>
<li>WIERSZE ma wartość 8,</li>
<li>KOLUMNY ma wartość 8,</li>
<li>DLUGOSC ma wartość 5.</li>
</ul>

Program, w pętli:
<ul>
<li>pisze diagram aktualnego stanu planszy i wskazuje, który gracz ma wykonać ruch;</li>
<li>czyta polecenie gracza;</li>
<li>jeśli wczytał polecenie wykonania ruchu, wykonuje je;</li>
<li>jeśli wczytał polecenie przerwania gry, kończy pracę.</li>
</ul>

Pętla kończy się, gdy:
<ul>
<li>program dostanie polecenie przerwania gry, lub</li>
<li>jeden z graczy wygra.</li>
</ul>

Jeśli jeden z graczy wygra, to program, na zakończenie pracy, pisze diagram końcowego stanu planszy i informuje, kto wygrał.

Compilation and launching:
-------------------------

To **compile**, type command: **gcc @opcje -DWIERSZE=val1 -DKOLUMNY=val2 -DDLUGOSC=val3 01_fin.c -o 01**

**opcje** is a gcc configuration file, included in repo.<br>
**WIERSZE, KOLUMNY, DLUGOSC** - integers from 1 to 26 && DLUGOSC <= min(WIERSZE, KOLUMNY)

To **launch**, type command: **./01**

*specification provided by: MIM UW*
