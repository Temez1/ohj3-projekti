# Teekkarin Sekoilu Seikkailut (TSS) 🔥

Teekkarin sekoilu seikkailut on peli, jossa päähenkilö toimittaa ruokatilauksia nälkäisille Teekkareille. Tavoitteena on viedä tilaukset perille mahdollisimman nopeasti, jotta ruoka pysyy lämpimänä ja asiakkaat tyytyväisinä. Pelin voittaa, kun on kerännyt tarpeeksi rahaa maksaakseen opintolainan takaisin. 🔥 🔥 🔥

## Tekninen dokumentointi

### Sisällysluettelo

- [Yleiskatsaus](#yleiskatsaus)
- [Graafisten objektien tyypit](#graafisten-objektien-tyypit)
- ..

### Yleiskatsaus

Projektin rakenne on hyvin yksinkertainen. TeekkarinSekoiluSeikkailut kansiosta löytyy varsinainen peli ja UnitTestes kansiosta yksikkötestit luokille, joille on koettu olevan tarpeellista toteuttaa yksikkötestit. Tarpeellisella tarkoitetaan paljon logiiikkaa sisältäviä luokkia, kuten pelaaja ja bussilinja.

Projektin arkkitehtuuri syntyi tehdessä, eli kokeillen eri tapoja ja pyrkien noudattamaan hyviä tapoja. Teknistä velkaa käsiteltiin siten, että projektin alkuvaiheessa pyrittiin välttämään sitä ja loppuvaiheessa sitä otettiin, koska projektin loputtua ei sitä tarvitse enää maksaa. Tosin jatkokehitysmahdollisuuksia pidettiin mielessä eri ominaisuuksia tehdessä, joten aivan fiasko ei lopputulos pitäisi olla. Tarkempaa arvioita kuinka hyvä projektin arkkitehtuuri on tai jatkokehitysmahdollisuudet ovat, on kuitenkin vaikeaa arvioida etukäteen kokemattomuuden takia.

### Kansiorakenne

Pelikansion juuresta löytyy kaksi kansiota, UI ja gameObjects, sekä peliluokka "Game" ja kolme läheisesti peliluokkaan liittyviä tiedostoja: GameObjects, initScene ja MainMenu.


### Graafisten objektien tyypit

Graafisten objektien tyyppejä käytetään objektin tunnistamiseen pelissä (scenessä).  
Graafisten objektien tyypit ovat määritelty kyseisen objektin type metodissa header tiedostossa. Lisätiedot Qt [docista](https://doc.qt.io/qt-5/qgraphicsitem.html#type).

| Type              | Value         |
|-------------------|---------------|
| Bus               | UserType + 1  |
| Player            | UserType + 2  |
| Stop              | UserType + 3  |
| Kiosk             | UserType + 4  |
