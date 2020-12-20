# GenericNetworkSender
Generic Network App for sending data between server and client(s)



Jak skompilować:

```
make mstuff
```


uruchom serwer, uruchom klienta, podaj adres serwera.

Przy udanym połączeniu w kliencie pojawi się symbol zachęty ```>>```.

Słownik poleceń:

```exit``` - przerwanie połączenia z serwerem

```dummy X``` - zapytanie o wysłanie pliku z losowymi danymi o wielkości X bitów (X musi być większe od zera)

Po udanym pobraniu z serwera, plik będzie się znajdował w tym samym folderze co program-klient, pod nazwą "dummy_recieved.txt" 
