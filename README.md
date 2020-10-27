# Teekkarin Sekoilu Seikkailut (TSS) 🔥

Teekkarin sekoilu seikkailut on peli, jossa päähenkilö toimittaa ruokatilauksia nälkäisille Teekkareille. Tavoitteena on viedä tilaukset perille mahdollisimman nopeasti, jotta ruoka pysyy lämpimänä ja asiakkaat tyytyväisinä. Pelin voittaa, kun on kerännyt tarpeeksi rahaa maksaakseen opintolainan takaisin. 🔥 🔥 🔥

## Tekninen dokumentointi

### Sisällysluettelo

- [Graafisten objektien tyypit](#graafisten-objektien-tyypit)
- ..

### Graafisten objektien tyypit

Graafisten objektien tyyppejä käytetään objektin tunnistamiseen pelissä (scenessä).  
Graafisten objektien tyypit ovat määritelty kyseisen objektin type metodissa header tiedostossa. Lisätiedot Qt [docista](https://doc.qt.io/qt-5/qgraphicsitem.html#type).

| Type              | Value         |
|-------------------|---------------|
| Bus               | UserType + 1  |
| Player            | UserType + 2  |
| Stop              | UserType + 3  |
