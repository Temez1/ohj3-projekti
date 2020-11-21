# Teekkarin Sekoilu Seikkailut (TSS) 🔥

Teekkarin sekoilu seikkailut on peli, jossa päähenkilö toimittaa ruokatilauksia nälkäisille Teekkareille. Tavoitteena on viedä tilaukset perille mahdollisimman nopeasti, jotta ruoka pysyy lämpimänä ja asiakkaat tyytyväisinä. Pelin voittaa, kun on kerännyt tarpeeksi rahaa maksaakseen opintolainan takaisin. 🔥 🔥 🔥

## Tekninen dokumentointi

### Sisällysluettelo

- [Yleiskatsaus](#yleiskatsaus)
- [Kansiorakenne](#kansiorakenne)
- [Luokkajako](#luokkajako)
- [Graafisten objektien tyypit](#graafisten-objektien-tyypit)
- [Kritiikki](#kritiikki)

### Yleiskatsaus

Projektin rakenne on hyvin yksinkertainen. Kaikki on tehty käsin, eli nollasta on aloitettu ilman kurssin tarjoamaa kirjastoa. Syynä tähän oli muutamakin. Ensinnäkin kurssikirjaston dokumentaatio oli projektia aloittaessa (ihan ensimmäisellä viikolla kun se julkaistiin) todella heikko. Sitä ei oikeastaan ollut laisinkaan, luokkajako lisättiin myöhemmin. Toinen syy oli, että selaillessa kurssin kirjastoa emme oikeen nopeasti katsottuna päässeet perille miten sitä tulisi käyttää, koska ei ollut mitään yleiskatsausta. Luottamus oli siis heikko, joten näimme paremmaksi vaihtoehdoksi toteuttaa asiat itse. Emme myöskään halunneet olla riippuvaisia kurssikirjaston mahdollisista puutteista. Halusimme myös oppia tekemään ratkaisut itse ja mitä asioita pitää ottaa huomioon isompaa projektia tehdessä.

TeekkarinSekoiluSeikkailut kansiosta löytyy varsinainen peli ja UnitTestes kansiosta yksikkötestit luokille, joille on koettu olevan tarpeellista toteuttaa yksikkötestit. Tarpeellisella tarkoitetaan paljon logiiikkaa sisältäviä luokkia, kuten pelaaja ja bussilinja.

Projektin arkkitehtuuri syntyi tehdessä, eli kokeillen eri jaottelua, pyrkien noudattamaan hyviä tapoja ja paljon refaktorointia välissä.

Teknistä velkaa käsiteltiin siten, että projektin alkuvaiheessa pyrittiin välttämään sitä ja loppuvaiheessa sitä otettiin, koska projektin loputtua ei sitä tarvitse enää maksaa. Tosin jatkokehitysmahdollisuuksia pidettiin mielessä eri ominaisuuksia tehdessä, joten aivan fiasko ei lopputulos pitäisi olla. Ja tottakai arvostelua toteutuksen laadun suhteen pidettiin myös mielessä alusta loppuun.

Tarkempaa arvioita kuinka hyvä projektin arkkitehtuuri on tai jatkokehitysmahdollisuudet ovat, on kuitenkin vaikeaa arvioida etukäteen kokemattomuuden ja ohjelmistojen jatkotarpeiden arvaamattomuuden takia.

### Kansiorakenne

Pelikansion juuresta löytyy kaksi kansiota, UI ja gameObjects, sekä peliluokka "Game" ja kolme läheisesti peliluokkaan liittyviä tiedostoja: GameObjects, initScene ja MainMenu. GameObjects luokka tallentaa vain tietyt peliobjektit muistiin, joita ei joko lisätä sceneen, tai on muuten kätevä tallentaa myöhempää refereointia varten (Pelaaja). initScene on vain aputiedosto, josta löytyy pelin alustamiseen liittyviä asioita ja header filestä configuraatio vakiot. MainMenu on mainmenu dialogi, joka käynnistetään pelin alussa.

gameObjects kansio koostuu kahdesta kansiosta, graphical ja handlers, sekä parista tiedostosta. Idea on, että graphical kansio sisältää pelin sceneen lisättävät graafiset objektit, jotka siis näkyvät pelissä ja assets kansion, mistä löytyy kaikki grafiikat svg muodossa ja Qt:n resurssitiedosto. Svg siitä syystä, että peliruudun skaalautuessa kuvat pysyvät tarkkoina, koska vektorigrafiikka. Handlers kansiosta löytyy luokat, jotka käsittelevät näitä pelissä olevia objekteja. Esimerkiksi TeekkariHandler käsittelee teekkareita, kuten niiden lisäämistä ja poistamista skenestä. Loput pari tiedostoa ovat logiisia luokkia, jotka eivät siis esiinny skenesse visuaalisesti. Wallet on pelaajan lompakko, joka käsittelee rahan ja BusLine on bussilinja, mikä käsittelee pysäkkejä ja tarjoaa busslinjan bussille.

UI kansio on suht tynkä. Suurin osa UI componenteistä oli QT:n valmiita, mutta täältä löytyy ProgressBar, joka on modattu Qt:n progress bar.

### Luokkajako
Kaksi kuvaa, toiminnallinen ja täydellinen.

"luokka" = Toiminalliset riippuvuudet. Eli kutsuu luokan metodeja (1 tai enemmän) ja näin ollen on riippuvainen luokan toiminallisiista riippuvuksista.
(Toiminnallisessa & täydellisessä kuvassa suora nuoli riippuvuuteen)

"(luokat)" = Riippuvuus olemasssaolosta. Eli käytännössä tallentaa luokan vain muistiin, mutta ei käytä luokan toiminnallisuutta mitenkään hyväksi (metodikutsuja nolla). Näin ollen luokan toiminallisuus voi muuttua miten vain, vaikuttamatta luokan toimintaan millään tavalla. Tämä riippuvuus ei ole siis ohjelmoijan näkökulmasta kriittinen kun mietitään muutosten vaikutusta ohjelman käyttäytymiseen.
(Täydellisessä kuvassa katkoviiva nuoli riippuvuuteen)

Signals = Luokan signaalit
(Kuvassa aaltoileva nuoli mihin ollaan kytketty)


Game -> GameObjects, ProgressBar, initScene, (MainMenu)

initScene -> ProgressBar, (GameObjects, BusLine, TeekkariHandler, BusLineHandler, Bus, Stop, Kiosk, Player, Food, Lautanen)

GameObjects -> (BusLineHandler, TeekkariHandler, Player)

gameObjects/

  BusLine -> Stop

  Wallet
    Signals: balanceChanged(int balance)

  graphical/

    Bus -> BusLine, Stop

    Food
      Signals: foodStateChanged(Food *sender, int state);

    Kiosk -> Food

    Player -> Bus, Stop, Kiosk, Wallet, Lautanen, (Food, )
      Signals: playerOutOfMoney, playerOrderedFood, playerDeliveredFood

    Stop -> (Kiosk, Teekkari)

    Teekkari -> Food
      Signals: teekkariReceivedFood(Teekkari *sender);

  handlers/

    BusLineHandler -> (BusLine)

    TeekkariHandler -> Teekkari, BusLineHandler, BusLine, Stop

UI/
  ProgressBar
    Signals: enoughMoneyToPayStudentLoan

### Graafisten objektien tyypit

Graafisten objektien tyyppejä käytetään objektin tunnistamiseen pelissä (scenessä).  
Graafisten objektien tyypit ovat määritelty kyseisen objektin type metodissa header tiedostossa. Lisätiedot Qt [docista](https://doc.qt.io/qt-5/qgraphicsitem.html#type).

| Type              | Value         |
|-------------------|---------------|
| Bus               | UserType + 1  |
| Player            | UserType + 2  |
| Stop              | UserType + 3  |
| Kiosk             | UserType + 4  |

### Kritiikki

#### Kansiorakenne
Busslinja on välimaaston tapaus. Busslinja on tavallaan jo (pysäkkien) käsittelijä, mutta se luokiteltiin loogiseksi luokiksi eikä sijoitettu handlers kansioon sekavuuden välttämiseksi. Tasoja oli siis kolme (pysäkki "Stop", busslinja "BusLine", bussilinjat "BusLineHandler"), eli ehkä toisenlainen luokittelu olisi ollut sopivampi jatkoakin ajatellen.

Food ei oo graafinen objekti, vaan looginen. Alkuperäisen ajatuksen ja laiskuuden takia jäänyt väärän paikkaan.

#### Luokkajako

TeekkariHandler selvästi ylittää rajoja ja on riippuvainen osa-alueista, jotka eivät sille kuulu. Riippuvuuksien karsimiseksi, pitäsi BusLineHandleri riittää tekemään tarvittavat toimenpiteet teekkareille. Esim. findRandomStopWithoutTeekkarissa pysäkkeihin ja busslinjoihin liittyvät asiat pitäsi siirtää kokonaan BusLineHandlerin vastuulle, samoin destroyTeekkarissa ja spawnTeekkarissa.

Näin ollen riippuvuuksia olisi enää luonnolliset Teekkari ja BusLineHandler. Abstraktio taso olisi myös samalla tasolla ja operoisi järkeväämin myös jatkokehityksen kannalta.