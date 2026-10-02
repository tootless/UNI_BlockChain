# Maišos funkcija

### Mokymosi tikslais, parašyta C++

# v1.0 2-10-2026

# Reikalavimai

## 1. Veikianti 256 bitų maišos funkcija
Funkcija yra maždaug O(n) kompleksijos. To pasėkmės matomos v1.0 efektyvumo tyrime.
## Pakankamai skirtingos išvestys
Išvestys skiriasi ir kai yra maži pakeitimai.  
Per visus darytus testus, žodžiai nesikartojo.  
Kolizijų kol kas yra daug, tačiau funkcija turi neapibrėžtą ir netestuotą, tačiau šiai versijai pakankamai gerą "avalanche" efektą.  
Vėlesnėmis versijomis funkcija bus tobulinama ir tuomet bus atlikti testai.

## Įvestis
### Bendri teksto reikalavimai
Maišos funkcija veikia su tuščia, trumpesne, tokia pat bei ilgesne (visomis) ilgio įvestimis.  
Programa palaiko rankinį bei failo įvesties būdus. Tai galima pasirinkti įrašant skaičių (1 - failas, 2 - rankinis).  
Tarpai įvestyje nėra šalinami, patys baitai nėra keičiami.  
### Failo skaitymas
Failas skaitomas std::ios::binary būdu, todėl maišomas failo turinys baitas po baito be teksto redagavimo, kodavimo konvertavimo ar eilučių pabaigų keitimo.  
Jei failas neatsidaro arba neperskaitomas, tai pranešama kaip apie klaidas ir programa sustoja. 
### Rankinis įvedimas 
```std::getline(std::cin)``` naudojamas teksto nuskaitymui, tad `Enter` klavišo paspaudimas nepatenka į maišos baitus.
```std::string``` jau saugo neapdorotus baitus, todėl kai tekstas yra UTF-8,  
```text.begin(), text.end()``` tiesiogiai nukopijuoja UTF-8 baitų seką be perkodavimo.  

## Išvestis  
Sukurta maišos funkcija turi fiksuotą 256 bitų išvestį:
```state_wcount = 8``` (žodžiai po 32 bitus) priverčia visada duoti lygiai 256 bitų rezultatą.  
```to_hex()``` funkcija duoda maišos rezultatą:  
Rezultatas vaizduojamas hex skaitmenimis, visada mažosiomis raidėmis ir su pradiniais nuliais išsaugotais.  

## Determinizmas
Tie patys baitai duoda tokias pat maišos reikšmes. ```<random>, <chrono>``` bibliotekos yra naudojamos tik testavimo reikmėms.
Taip pat atliktas testas (programoje matomas pasirinkus ```menu = 3```), kuris patikrina seką A, B, A.

## 3. Efektyvumas
Laikas buvo išmatuotas su didėjančiomis įvestimis ir yra pavaizduotas žemiau

### v1.0 Maišos funkcijos efektyvumo tyrimas

Matuojamas ```hash_block()``` skaičiavimo laikas, didėjant įvesties dydžiui. Naudota ta pati ```rand()``` sėkla (25) kiekviename paleidime, kad duomenys būtų tokie pat visuose trijuose paleidimuose.  
Tyrimui naudojama Visual Studio built-in O2 optimizacija su Release konfiguracija.  

| Ivesties dydis (simboliai) | 1-as | 2-as | 3-ias | Vidurkis (s) |
|---|---|---|---|---|
| 1 000 000 | 0.002 | 0.002 | 0.002 | 0.002 |
| 10 000 000 | 0.025 | 0.028 | 0.023 | 0.025 |
| 100 000 000 | 0.237 | 0.253 | 0.248 | 0.246 |

Taip pat galima matyti nuotraukas konsolės, kurią naudojau testams atlikti (pav.1, pav.2, pav.3).  
```system("pause")``` tarp matavimų yra naudojama su noru, kad nebūtų netikėtų trikdžių.

### Išvada: 
Laikas auga maždaug proporcingai įvesties dydžiui, tai atitinka O(n) maišos funkcijos sudėtingumą.

### Efektyvumo paveikslėliai
!["test1.png"](/assets/v1.0/test1.png)
!["test2.png"](/assets/v1.0/test2.png) 
!["test3.png"](/assets/v1.0/test3.png) 