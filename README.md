# client-server
Zadatak 3:
Razviti GNU GCC server koji je baza podataka o informacijama 10 najbitnijih aktivnih MI6
operativaca. Baza podataka treba da sadrži ime, prezime i trenutnu lokaciju na kojoj se operativac nalazi
(Israel, Tunis, Srbija, ....).
Komunikacija sa serverom se odvija preko TCP/IP protokola na sledeći način:
Klijent -> Server: NEEDINFO
Server -> Klijent : YOUCANGETINFO
Klijent -> Server : JAMESBOND
Server -> Klijent : DUSANPOPOVSERBIA
Ukoliko klijent želi da završi komunikaciju treba da pošalje sledeće:
Klijent -> Server: ENDE
Nakon čega server odgovara:
Server -> Klijent : ENDE
Da bi se dobila informacija neophodno je nakon YOUCANGETINFO poruke uneti alter ego
agenta (lažno ime), nakon čega server vraća prave informacije o obavestajcu.
Realizovati klijent aplikaciju koja pristupa pomenutom serveru poštujući gore navedene korake.
Ukoliko neki korak nije ispoštovan, komunikacija se prekida.(10p)
Koristiti cezarovu enkripciju prilikom komunikacije servera i klijenta. Da bi se komunikacija
omogućila klijent mora da poseduje ključ za pravilno enkriptovanje i dekriptovanje poruka kako
nalaže cezarova enkripcija (7p).
Omogućiti da više klijenata istovremeno ima pristup jednom serveru (3p).
https://en.wikipedia.org/wiki/Caesar_cipher
Komunikacija između klijenta i servera se izvršava pomoću TCP/IP protokola. Server prihvata
konekcije na proizvoljnom portu (ne koristiti standardni port 80) i odgovara zahtevima pristiglim od strane klijenta.
