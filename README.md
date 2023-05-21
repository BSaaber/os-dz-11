# Мовшин Максим | БПИ213 | ДЗ-11
компиляция:
```
make all
```
запуск (Сервер)
```
sudo ./TCPEchoServer <server_port>
```

запуск (Клиент)
```
sudo ./TCPEchoClientLoop <server_ip> <server_port> <own listening port>
```
формат сообщения:
```
<reciever ip>:<reciever port>|<message>
```
## пример арботы
Ввод - Терминал 1 (Сервер):
```
sudo ./TCPEchoServer 349
```
Ввод - Терминал 2 (Клиент 1):
```
sudo ./TCPEchoClientLoop 127.0.0.1 349 13
```
Ввод - Терминал 3 (Клиент 2):
```
sudo ./TCPEchoClientLoop 127.0.0.1 349 12
127.0.0.1:13|hello from 12
```
Вывод - Терминал 2 (Клиент 1):
```
hello from 12
```
Ввод - Терминал 2 (Клиент 1):
```
127.0.0.1:12|The End
```

