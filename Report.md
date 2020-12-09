# Tagok

| Név | Github azonosito  | Javasolt relatív érdemjegy | Becsült óra | Indoklás  |
| --- | ---- | --- | ------------------ | --------- |
| Takács Richárd | @ricsi114 | -3 | 0 | - |
| Fekete Martin | @martinfekete17 | -3 | 3 | Ellenőrizte a pull requesteket. |
| Lengyel Márk | @LengyHELL | 0 | 55-65 | Csinálta a kódot, dokumentációt, unit teszteket, kiírta a pull requestet stb. |


# Videók

 - [Gameplay](/videos/gameplay.mp4)
 - [CodeBaseDefense](/videos/codebasedefense.mp4)

# Befejezett feladatok

| Feladat | Merge ideje a határidóhöz (nap) | Change request körök | Reviewer |
| ------- | ------------------------------- | -------------------- | -------- |
| Feladat 1 | 0 | 1 | @wajzy |
| Feladat 2 | +4 | 1 | @wajzy |
| jsonparser | +8 | 1 | @wajzy |
| levelup | -4 | 1 | @oliverosz |
| attackspeed | -7 | 0 | @vizvezetek |
| documentation | folyamatosan frissült | - | - |
| unittest | +6 | 0 | @hmartin28 / @martinfekete17, @LengyHELL |
| makefile | 0 | 2 | @hegyhati |
| refactor | -2 | 0 | @hegyhati |
| docker | 0 | 0 | @hegyhati |
| jsonpimp | Merge: 11.24 | 0 | @hmartin28 / @martinfekete17, @LengyHELL |
| map | Merge: 12.03 | 0 | @hmartin28 / @martinfekete17, @LengyHELL |
| game | Merge: 12.03 | 0 | @hmartin28 / @martinfekete17, @LengyHELL |
| defense | Merge: 12.06 | 0 | @hmartin28 / @martinfekete17, @LengyHELL |
| damage | Merge: 12.06 | 0 | @hmartin28 / @martinfekete17, @LengyHELL |
| markedmap | Merge: 12.06 | 0 | @hmartin28 / @martinfekete17, @LengyHELL |
| preparedgame | Merge: 12.06 | 0 | @hmartin28 / @martinfekete17, @LengyHELL |
| light radius | Merge: 12.07 | 0 | @hmartin28 / @martinfekete17, @LengyHELL |
| rendering | Merge: 12.08 | 0 | @hmartin28 / @martinfekete17, @LengyHELL |

# Unit tesztek

| Osztály | Publikus metódusok száma | Unit tesztelt metódusok száma | Unit tesztek száma |
| --- | --- | --- | --- |
| `Monster` | 13 | 10 | 3 |
| `Hero` | 8 | 5 | 4 |
| `JSON` | 6 | 4 | 5 |
| `Map` | 6 | 4 | 2 |
| `MarkedMap` | 4 | 4 | 2 |
| `Game` | 14 | 6 | 2 |
| `PreparedGame` | 2 | 1 | 1 |
| `Renderer` | 3 | 0 | 0 |
| `TextRenderer` | 4 | 0 | 0 |
| `ObserverTextRenderer` | 4 | 0 | 0 |
| `HeroTextRenderer` | 4 | 0 | 0 |
| `SVGRenderer` | 3 | 0 | 0 |
| `ObserverSVGRenderer` | 3 | 0 | 0 |
| `HeroSVGRenderer` | 3 | 0 | 0 |

# Kód dokumentáció

| Teljesen dokumentált osztályok | Részben dokumentált osztályok | Nem dokumentált osztályok |
| --- | --- | --- |
| `Monster` | - | - |
| `Hero` | - | - |
| `JSON` | - | - |
| `Map` | - | - |
| `MarkedMap` | - | - |
| `Game` |  - | - |
| `PreparedGame` | - | - |
| `Renderer` | - | - |
| `TextRenderer` | - | - |
| `ObserverTextRenderer` | - | - |
| `HeroTextRenderer` | - | - |
| `SVGRenderer` | - | - |
| `ObserverSVGRenderer` | - | - |
| `HeroSVGRenderer` | - | - |


# Mindenféle számok

 - Összes cpp kódsor : ~17300
 - Egyéb kódsor (make,doxyfile,shellscript, ...) : ~800
 - cppcheck
   - warning : 0
   - style : 1
   - performance : 0
   - unusedFunction : 0
   - missingInclude : 0

# Implicit megtanult dolgok

 - egy kis shellscript
 - olyasféle fájl parzolás
 - svg fájlok

# Feedback

A legjobban a renderer rész tetszett, ez volt a leglátványosabb, tetszett a monster - hero csatázós rész is, viszont kicsit arra számítottam, hogy inkább csak az 1v1, fegyverek, itemek stb. irányba megyünk majd, de összességében tetszett így is.
