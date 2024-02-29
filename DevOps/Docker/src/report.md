## Part 1. Готовый докер

ЗАДАЧА: Взять официальный докер-образ с nginx и выкачать его при помощи `docker pull`

- Запускаем Docker и в терминале вызываем команду `docker pull nginx`

Вывод `docker pull nginx`
![](./screenshots/1.1.png)

- ЗАДАЧА: Проверить наличие докер-образа через `docker images`.

Вывод `docker images`
![](./screenshots/1.2.png)

- ЗАДАЧА: Запустить докер-образ через `docker run -d [image_id|repository]`

Вывод `docker run -d nginx`
![](./screenshots/1.3.png)

- ЗАДАЧА: Проверить, что образ запустился через `docker ps`

Вывод `docker ps`
![](./screenshots/1.4.png)

- ЗАДАЧА: Посмотреть информацию о контейнере через `docker inspect [container_id|container_name]`

Вывод `docker inspect distracted_driscoll`
![](./screenshots/1.5.png)

- ЗАДАЧА: По выводу команды определить и поместить в отчёт размер контейнера, список замапленных портов и ip контейнера

Размер контейнера\
![](./screenshots/1.6.png)

Список замапленных портов\
![](./screenshots/1.7.png)

ip контейнера\
![](./screenshots/1.8.png)

- ЗАДАЧА: Останови докер образ через `docker stop [container_id|container_name]`

Вывод `docker stop distracted_driscoll`
![](./screenshots/1.9.png)

- ЗАДАЧА: Проверить, что образ остановился через `docker ps`

Вывод `docker ps`
![](./screenshots/1.10.png)


- ЗАДАЧА: Запустить докер с портами 80 и 443 в контейнере, замапленными на такие же порты на локальной машине, через команду *run*.

Вывод `docker run -d -p 80:80 -p 443:443 nginx`
![](./screenshots/1.11.png)

- ЗАДАЧА: Проверить, что в браузере по адресу localhost:80 доступна стартовая страница nginx

Вывод localhost:80
![](./screenshots/1.12.png)

ЗАДАЧА: Перезапустить докер контейнер через `docker restart [container_id|container_name]`

Вывод `docker restart practical_zhukovsky`
![](./screenshots/1.13.png)

- ЗАДАЧА: Проверить любым способом, что контейнер запустился

Вывод `docker ps`
![](./screenshots/1.14.png)

## Part 2. Операции с контейнером

- ЗАДАЧА: Прочитай конфигурационный файл nginx.conf внутри докер контейнера через команду exec

Вывод `docker exec nostalgic_hoover cat etc/nginx/nginx.conf`\
![](./screenshots/2.1.png)

- ЗАДАЧА: Создай на локальной машине файл nginx.conf

Выполняем команду `touch nginx.conf` в папке src текущего проекта и копируем в него вывод команды `docker exec nostalgic_hoover cat etc/nginx/nginx.conf`\
![](./screenshots/2.2.png)

- ЗАДАЧА: Настрой в нем по пути /status отдачу страницы статуса сервера nginx



- ЗАДАЧА: Скопируй созданный файл *nginx.conf* внутрь докер-образа через команду `docker cp`



- ЗАДАЧА: Перезапусти nginx внутри докер-образа через команду exec



- ЗАДАЧА: Проверь, что по адресу localhost:80/status отдается страничка со статусом сервера nginx



- ЗАДАЧА: Экспортируй контейнер в файл container.tar через команду export



- ЗАДАЧА: Останови контейнер



- ЗАДАЧА: Удали образ через `docker rmi [image_id|repository]`, не удаляя перед этим контейнеры



- ЗАДАЧА: Удали остановленный контейнер



- ЗАДАЧА: Импортируй контейнер обратно через команду import



- ЗАДАЧА: Запусти импортированный контейнер



- ЗАДАЧА: Проверь, что по адресу *localhost:80/status* отдается страничка со статусом сервера nginx




- В отчёт помести скрины:
  - вызова и вывода всех использованных в этой части задания команд;
  - содержимое созданного файла *nginx.conf*;
  - страницы со статусом сервера **nginx** по адресу *localhost:80/status*.