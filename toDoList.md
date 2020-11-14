## To do list:
### Kérdések:
  - [x] a ***Display*** (start-stop) modul Arduino-ról kapja az értékeket?
  - [x] a ***Display*** modul tial-számlálói: _**Total**_: minden aktív stimulus egybe, _**Reward**_, _**Air puff**_, _**Tail shock**_ és _**Empty**_
  - [x] *__p8__*-*__p9__* viszonya: a *__p9__* vezérli a berregőt a *Tone()* beépített fuggvénnyel, a *__p8__* folyamatosan világít, amíg a a berregő szól
  
### Nov. 26-ig megvalósítható feladatok:
  - [x] ***Start*** utáni váltakozó jelzővillogás kivétele (debug logikai változóval ki-be kapcsolgható [global_variables.h](/arduino/ToneStimTrial04/global_variables.h) )
  - [x] **US** hossza: ha 0, akkor a default a ***Tail shock***
  - [x] **Reset** debug: nincs owerflow
  - [ ] **színvilág** egyszerű allíthatósága a [GlobalParameters.py](/python/GlobalParameters.py) fájlbó
  - [ ] ***Display*** modul: +1 digital input, +1 analog input értékkijelző beszúrása
  - [ ] **protocol**: gyorsabb olvasás a *PC* felől
  
### Nagyobb feladatok - várhatóan nov. 26. után megvalósíthatóak:
  - [ ] ***gap***: ha negatív, az **US** ennyivel a **CS** befejezése előtt indul
  - [ ] **paraméter** értékbevitel: funkcionális le-föl gombok
  - [ ] a teljes **panel** átszerkesztése
  - [ ] **bug**: néha újra kell indítani (pontosítandó)
