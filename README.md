# GenericNetworkSender
Generic Network App for sending data between server and client(s)



Jak skompilować:

```
make mstuff
```


uruchom serwer, uruchom klienta, podaj adres serwera

przy udanym połączeniu w kliencie pojawi się symbol zachęty ```>>```
słownik poleceń:

exit - przerwanie połączenia z serwerem
dummy X - zapytanie wysłanie pliku z losowymi danymi o wielkości X bitów (X musi być większe od zera)

po udanym pobraniu z serwera, plik będzie się znajdował w tym samym folderze co program-klient, pod nazwą "dummy_recieved.txt" 
