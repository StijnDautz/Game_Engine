Studentnummer:
Stijn Dautzenberg	: 5961904
Jacco Mook		: 5917875

In de Constants.h file kunnen variabele geset worden

Deze raytracer is ingeleverd op 30 mei voor 24:00.
Het is gebouwd op een zelfgeschreven c++ engine. Dit koste ons wat extra tijd, maar het was wel erg leerzaam.
Deze engine is niet volledig voorzien van commentaar, dit is nu ook niet relevant, maar het zal wel gebeuren voor P3.
Het bevat de features:
- Alle eisen voor een 6
- Textures voor alle primitives
- Normal mapping
- Multithreading (het splitsen van de image in rows, blokken zouden nog efficienter zijn geweest, ivm cache)
- Anti alliasing

Textures and normal mapping
Een RaytracerObj heeft een texture en een normal component pointer.
Op deze manier is het gemakkelijk om verschillende materialen te maken.

Camera rotation:
Het is mogelijk om de camera te roteren in iedere richting.
In de applicatie zelf hebben we dit gelimiteerd tot de y-as, om te voorkomen dat de camera "rolt".
De the orientatie kan wel gezet worden in de code. 
Dit hebben wij ook gedaan om een mooi shot te realiseren wanneer je de applicatie opent.

Debugger:
De debugger laat alle gevraagde rays zien en is een aparte loop.
Het bevat geen multithreading of antialliasing. Dit zou de output namelijk kunnen aantasten.

Controls:
W - forward
A - left
S - backwards
D - right
Q - up
E - down
M - switch mode (debug - highperformance) let op deze functie gebruikt IsKeyDown, IsKeyPressed is niet geïmplementeerd.
R - camera to origin

The code bevat veel casting foutjes, die zijn er door de tijd heen ingeslopen. 
Ze hebben geen effect op het resultaat, maar het is wel iets wat ik de komende weken nog wil corrigeren. (OCD lol)