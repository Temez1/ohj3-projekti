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

Projektin rakenne on hyvin yksinkertainen. Kaikki on tehty käsin, eli nollasta on aloitettu ilman kurssin tarjoamaa kirjastoa. Syynä tähän oli muutamakin. Ensinnäkin kurssikirjaston dokumentaatio oli projektia aloittasse (ihan ensimmäisellä viikolla kun se julkaistiin) todella heikko. Sitä ei oikeastaan ollut laisinkaan, luokkajako lisättiin myöhemmin. Toinen syy oli, että selaillessa kurssin kirjastoa emme oikeen nopeasti katsottuna päässeet perille miten sitä tulisi käyttää, koska ei ollut mitään yleiskatsausta. Luottamus oli siis heikko, joten näimme paremmaksi vaihtoehdoksi toteuttaa asiat itse. Emme siis halunneet olla riippuvaisia kurssikirjaston mahdollisista puutteista. Halusimme myös oppia tekemään ratkaisut itse ja mitä asioita pitää ottaa huomioon isompaa projektia tehdessä.

TeekkarinSekoiluSeikkailut kansiosta löytyy varsinainen peli ja UnitTestes kansiosta yksikkötestit luokille, joille on koettu olevan tarpeellista toteuttaa yksikkötestit. Tarpeellisella tarkoitetaan paljon logiiikkaa sisältäviä luokkia, kuten pelaaja ja bussilinja.

Projektin arkkitehtuuri syntyi tehdessä, eli kokeillen eri jaottelua, pyrkien noudattamaan hyviä tapoja ja paljon refaktorointia välissä. Teknistä velkaa käsiteltiin siten, että projektin alkuvaiheessa pyrittiin välttämään sitä ja loppuvaiheessa sitä otettiin, koska projektin loputtua ei sitä tarvitse enää maksaa. Tosin jatkokehitysmahdollisuuksia pidettiin mielessä eri ominaisuuksia tehdessä, joten aivan fiasko ei lopputulos pitäisi olla. Ja tottakai arvostelua toteutuksen laadun suhteen. Tarkempaa arvioita kuinka hyvä projektin arkkitehtuuri on tai jatkokehitysmahdollisuudet ovat, on kuitenkin vaikeaa arvioida etukäteen kokemattomuuden ja ohjelmistojen jatkotarpeiden arvaamattomuuden takia.

### Kansiorakenne

Pelikansion juuresta löytyy kaksi kansiota, UI ja gameObjects, sekä peliluokka "Game" ja kolme läheisesti peliluokkaan liittyviä tiedostoja: GameObjects, initScene ja MainMenu. GameObjects luokka tallentaa vain tietyt peliobjektit muistiin, joita ei joko lisätä sceneen, tai on muuten kätevä tallentaa myöhempää refereointia varten (Pelaaja). initScene on vain aputiedosto, josta löytyy pelin alustamiseen liittyviä asioita. MainMenu on mainmenu dialogi, joka käynnistetään pelin alussa.

gameObjects kansio koostuu kahdesta kansiosta, graphical ja handlers, sekä parista tiedostosta. Idea on, että graphical kansio sisältää pelin sceneen lisättävät graafiset objektit, jotka siis näkyvät pelissä. Handlers kansiosta löytyy luokat, jotka käsittelevät näitä pelissä olevia objekteja. Esimerkiksi TeekkariHandler käsittelee teekkareita, kuten niiden lisäämistä ja poistamista skenestä. Loput pari tiedostoa ovat logiisia olioita, jotka eivät siis esiinny skenesse visuaalisesti. Wallet on pelaajan lompakko, joka käsittelee rahan ja BusLine on bussilinja, mikä käsittelee pysäkkejä ja tarjoaa busslinjan bussille.

UI kansio on suht tynkä. Suurin osa UI componenteistä oli QT:n valmiita, mutta täältä löytyy ProgressBar, joka on modattu Qt:n progress bar.

### Luokkajako

Game -> GameObjects, ProgressBar, MainMenu & initScene




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

Busslinja on välimaaston tapaus. Busslinja on tavallaan jo (pysäkkien) käsittelijä, mutta se luokiteltiin loogiseksi olioksi eikä sijoitettu handlers kansioon sekavuuden välttämiseksi. Tasoja oli siis kolme (pysäkki "Stop", busslinja "BusLine", bussilinjat "BusLineHandler"), eli ehkä toisenlainen luokittelu olisi ollut sopivampi jatkoakin ajatellen. Tämä ei kuitenkaan vaikuta luokkajakoon luonnollisesti, siihen tämän tyylinen jaottelu on mielestäni hyvä. Vain tiedostojakoon eli kansiorakenteeseen.
