# palindromic-connect-four
my C implementation of connect-four game in "palindromic mode"

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
