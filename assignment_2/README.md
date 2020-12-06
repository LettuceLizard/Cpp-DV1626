Inlämningsuppgift 2 , 'Media Manager'
=====================================

Mall att utgå från:

Vad ska du göra?
----------------
Mattias har bara tre sorters medier hemma, PlayStation2-spel, vinylskivor samt
böcker. Han behöver en mediehanterare för att hålla koll på sina media. I och
med att han älskar C++, textgränssnitt och program som körs från terminalen
blir din uppgift att skapa ett program som körs från terminalen där han kan
mata in sina olika media och sedan printa ut dem i sin  terminal. Du behöver
inte spara biblioteket på disk (om du inte vill). 

Mattias har skickat med en klass för att enkelt kunna hantera tid, exempelvis
längd på en skiva eller ett spår. Den klassen heter `Time` och följer med.

Du ska skapa en arvshierarki med klasser enligt följande:

<img src="http://yuml.me/diagram/scruffy/class/[Media]^-[Ps2Game], [Media]^-[Book], [Media]^-[Vinyl]" >

Här är Media en abstrakt basklass vilken Ps2Game, Book och Vinyl ärver från.
Media skall ha en rent virtuell funktion `prettyPrint` med följande signatur:

```cpp
std::string prettyPrint()
```

Utöver metoden ovan ska de klasser som ärver från Media ha vissa metoder med
särskilda signaturer. Dessa används av testfall för att se att din lösning är
korrekt implementerad. Signaturerna följer nedan.

### Book
```cpp
Book(const std::string& title, const std::string& author,
     const std::string& isbn, int pages, int edition)
const std::string& getTitle()
const std::string& getAuthor()
const std::string& getIsbn()
int getPages()
int getEdition()
```

### Ps2Game
```cpp
Ps2Game(const std::string& title, const std::string& studio, int year)
const std::string& getTitle()
const std::string& getStudio()
int getYear()
```

### Vinyl och dess hjälpklasser

Vinyl har tre hjälpklasser. `Time` som följer med, `Track` och `VinylTypes`.
`VinylTypes` är en enum-klass med värdena `LONG_PLAY` och `EXTENDED_PLAY`.
`Track`-klassens signaturer följer nedan:

```cpp
Track(const std::string& name, const Time& length)
const std::string& getName()
const Time& getLength()
```

Vinylklassen har följande signaturer:

```cpp
Vinyl(const std::string& title, VinylTypes type, int year,
      const std::string& artist, const Time& runtime)
void addTrack(const Track& track)
const std::string& getTitle()
int getYear()
VinylTypes getType()
const std::string& getArtist()
const Time& getRuntime()
const std::vector<Track>& getTracks()
```

### MediaManager

Mediamanager är klassen som hanterar själva mediesamlingen. Den skall ha en
dynamiskt allokerad array av typen Media** (d.v.s. en dynamiskt allokerad array
med pekare till Media-instanser) så att alla media-instanser kan samlas i en
och samma array.

Notera att addMedia, addBook, addVinyl och addPs2Game tar emot en pekare
respektive en referens. Du kommer behöva göra en kopia och allokera i
MediaManager, förslagsvis m.h.a. copykonstruktorn. Du kan med andra ord
***inte*** bara ta pekaren i addMedia, eller ta addressen i övriga fall och
stoppa in i din dynamiska array.

```cpp
  MediaManager()
  void addMedia(Media* media)
  void addBook(const Book& book)
  void addVinyl(const Vinyl& vinyl)
  void addPs2Game(const Ps2Game& game)
  std::string printMedia()
  std::vector<Book> getBooks()
  std::vector<Vinyl> getVinyls()
  std::vector<Ps2Game> getPs2Games()
```

### För samtliga klasser
Utöver medlemsfunktionerna i klasserna listade ovan, skall `operator==`
implementeras så att instanser av dina klasser kan jämföras. ***Samtliga
medlemsfunktioner som hämtar data*** och inte ska påverka objektet (d.v.s. de
ska inte ändra på medlemmarna) ***skall*** vara markerade `const`.

### Hur kommer man igång?
Testfallen som besrkivs nedan kommer till att börja med fallera. Förslagsvis
börjar du med att implementera en av de enklare klasserna och löser sedan ett
testfall i taget. Jobba dig uppifrån och ned mot noll fallerande testfall.

Hur kompilerar jag och kör mitt program?
----------------------------------------
I mappen du fått finns det en makefil för att bygga och testa ditt program.
Bygg ditt program genom att köra `make clean all`.

Om du vill köra ditt program, skriv då `./app` på linux/macOS. Använder du WSL
på windows är det en liten linuxmaskin du jobbar i och då gör du som på linux.

Tester
------
Ett test som finns i katalogen `tests` kommer provköra din lösning för att se
att inlämningens regler är uppfyllda.

För att testa ditt program med testet finns det ett make-mål (eng. make
target). Kör det genom skriva `make clean test` i terminalen när du står i
samma katalog som makefilen.

***Testerna används för att verifiera att din inlämning faktiskt fungerar.
Ändra därför inte i test-main.cpp utan skapa istället en egen .cpp om du vill
testa din inlämning***.

Hur man testar med `Catch` ligger utanför scopet för denna kurs. För den
nyfikne som vill prova kan man dock titta på Catchs dokumentation:
https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md

Inlämning och examination
-------------------------
När alla tester går igenom och du är redo att lämna in kör du kommandot `make
zip`, givet att du är projektets mapp. Du kommer då få en zipfil i
projektmappen. Det är denna zipfil du ska lämna in på CodeGrade i rutan
nedanför.

Notera att det kan ta flera minuter för CodeGrade att bygga och testa din kod.
Om det inte ser ut att hända något kan det vara att testmiljön installeras för
att bygga och testa din kod.

För betyget G ska följande kriterier vara uppfyllda:

* Ditt program ska gå att kompilera.
* Ditt program ska passera alla testfall.
* Din kod ska hålla hålla god struktur. Kör `make static-code-analysis` och se
  till att du åtgärdat samtliga varningar och fel. CodeGrade kommer även köra
  detta.
* Du skall ha använt en dubbelpekare med dynamiskt allokerat minne.
* Minnet ska tas bort när det inte används. D.v.s Inga minnesläckor får
  förekomma. Kör `make memcheck` och säkerställ detta. CodeGrade kommer även
  köra detta.
* Ditt program ska gå att köra genom att starta det med `./app` och vara användbart.

Minnesläckor
------------
*Minnesläckeskontroll sker inte automatiskt när du kör testerna. Detta måste
göras manuellt enligt nedan.*

Tack vare att vi använder oss av kompilatorn clang kan vi enkelt kontrollera om
vi har minnesläckor i vårt program. Om du kompilerar ditt program med `make
memcheck` kommer du baka in funktionalitet för att skriva ut felmeddelanden när
ditt program läcker minne. När du kör ditt program efter att ha kompilerat med
`make memchec` kommer du, om du har minnesläckor att få en utskrift i stil med:

```
mattias@Osborne1:/mnt/c/Users/matti/Documents/bth/dv1627-assignment2-n-i-rad$ ./game

=================================================================
==7112==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 8 byte(s) in 1 object(s) allocated from:
    #0 0x4c429d in operator new[](unsigned long) (/mnt/c/Users/matti/Documents/bth/dv1627-assignment2-n-i-rad/game+0x4c429d)
    #1 0x4c6c46 in ConnectFour::ConnectFour(int, int, int) /mnt/c/Users/matti/Documents/bth/dv1627-assignment2-n-i-rad/src/ConnectFour.cpp:4:20
    #2 0x4c6b84 in main /mnt/c/Users/matti/Documents/bth/dv1627-assignment2-n-i-rad/main.cpp:11:15
    #3 0x7f56436770b2 in __libc_start_main /build/glibc-ZN95T4/glibc-2.31/csu/../csu/libc-start.c:308:16

SUMMARY: AddressSanitizer: 8 byte(s) leaked in 1 allocation(s).
```

* #0 Berättar att vi gör en `new[]`, alltså att vi skapar en ny array med `new`
  som läcker minne
* #1 Berättar att läckan finns i funktionen `ConnectFour::ConnectFour(int, int,
  int)` och på fjärde raden och 20e kolumnen i filen `src/ConnectFour.cpp`.
* #2 - #3 innehåller *call-stacken* till funktionen. D.v.s. vilka funktioner som
  programmet gått igenom för att komma till funktionen i #1 där läckan finns. I
  det här fallet anropar *operativsystemet* `__libc_start_main` som i sin tur
  anropar `main` i `main.cpp` som anropar `ConnectFour(int, int, int)` i
  `src/ConnectFour.cpp` (konstruktorn med tre parametrar) som är den funktion
  som läcker.

Minnesläckor i ditt program kan också hittas när man kör testerna. Du får då en
eller flera liknande utskrifter i din terminal beroende på hur många gånger
ditt program läckt under testkörningarna.

Statisk kodanalys
-----------------
*Statisk kodanalys sker inte automatiskt när du kör testerna. Detta måste göras
manuellt enligt nedan.*

Tack vare att vi använder oss av kompilatorn clang kan vi enkelt kolla efter
vanliga fel i vår källkod. Det kallas för *linting* eller statisk kodanalys.
D.v.s. analys av koden man kan göra utan att köra koden (analys som kräver att
koden körs kallas för dynamisk kodanalyas).

För att köra statisk kodanalys kör vi make-målet `static-code-analysis`. En
exempelkörning kan se ut såhär:

```
mattias@Osborne1:/mnt/c/Users/matti/Documents/bth/dv1627-assignment2-n-i-rad$ make static-code-analysis
clang-tidy  -header-filter=.* --checks="diagnostic-*, analyzer-*, readability-*, performance-*" src/ConnectFour.cpp main.cpp --  -Iinclude  -Itest/include
3 warnings generated.
3 warnings generated.
/mnt/c/Users/matti/Documents/bth/dv1627-assignment2-n-i-rad/src/ConnectFour.cpp:8:19: warning: method 'yellowPlays' can be made static [readability-convert-member-functions-to-static]
bool ConnectFour::yellowPlays(int col) {return true;}
                  ^
/mnt/c/Users/matti/Documents/bth/dv1627-assignment2-n-i-rad/src/ConnectFour.cpp:10:19: warning: method 'redPlays' can be made static [readability-convert-member-functions-to-static]
bool ConnectFour::redPlays(int col) {return true;}
                  ^
/mnt/c/Users/matti/Documents/bth/dv1627-assignment2-n-i-rad/src/ConnectFour.cpp:12:25: warning: method 'getCurrentStatus' can be made static [readability-convert-member-functions-to-static]
GameStatus ConnectFour::getCurrentStatus() const {
                        ^                  ~~~~~~
```

Här ser vi tre varningar med förbättringar som kan göras på vår kod. I det här
fallet så ger det oss tips om att någonting inte står rätt till.
Förbättringsförslagen som lämnas låter inte riktigt rimliga nämligen. Den här
metoden ska ju vara beroende av spelets läge, när `clang-tidy` säger att den
kan göras statisk, d.v.s. så att den ej har tillgång till medlemsvariabler, har vi
nog missat något.

Med verktyg som `clang-tidy` hittas ofta många buggar som annars hade lett till
konstiga fel eller kompletteringar.
