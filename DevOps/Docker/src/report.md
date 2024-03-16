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

Вывод `docker run -d -p 80:80 -p 443:443 nginx`\
![](./screenshots/1.11.png)

- ЗАДАЧА: Проверить, что в браузере по адресу localhost:80 доступна стартовая страница nginx

Вывод localhost:80\
![](./screenshots/1.12.png)

ЗАДАЧА: Перезапустить докер контейнер через `docker restart [container_id|container_name]`

Вывод `docker restart practical_zhukovsky`
![](./screenshots/1.13.png)

- ЗАДАЧА: Проверить любым способом, что контейнер запустился

Вывод `docker ps`
![](./screenshots/1.14.png)

## Part 2. Операции с контейнером

- ЗАДАЧА: Прочитать конфигурационный файл nginx.conf внутри докер контейнера через команду exec

Вывод `docker exec nostalgic_hoover cat etc/nginx/nginx.conf`\
![](./screenshots/2.1.png)

- ЗАДАЧА: Создать на локальной машине файл nginx.conf

Выполняем команду `touch nginx.conf` в папке src текущего проекта и копируем в него вывод команды `docker exec nostalgic_hoover cat etc/nginx/nginx.conf`\
![](./screenshots/2.2.png)

- ЗАДАЧА: Настроить в нем по пути /status отдачу страницы статуса сервера nginx\

Вывод `docker exec crazy_tharp cat etc/nginx/nginx.conf`\
![](./screenshots/2.3.png)

- ЗАДАЧА: Скопировать созданный файл *nginx.conf* внутрь докер-образа через команду `docker cp`

Вывод `docker cp nginx.conf crazy_tharp:/etc/nginx`\
![](./screenshots/2.4.png)

- ЗАДАЧА: Перезапустить nginx внутри докер-образа через команду exec

Вывод `docker exec crazy_tharp nginx -s reload`\
![](./screenshots/2.5.png)

- ЗАДАЧА: Проверить, что по адресу localhost:80/status отдается страничка со статусом сервера nginx

Вывод localhost:80/status\
![](./screenshots/2.6.png)

- ЗАДАЧА: Экспортировать контейнер в файл container.tar через команду export

Вывод `docker export -o container.tar crazy_tharp` и `ls`\
![](./screenshots/2.7.png)

- ЗАДАЧА: Остановить контейнер

Вывод `docker stop crazy_tharp` и `docker ps`\
![](./screenshots/2.8.png)

- ЗАДАЧА: Удалить образ через `docker rmi [image_id|repository]`, не удаляя перед этим контейнеры

Вывод `docker rmi -f nginx`\
![](./screenshots/2.9.png)

- ЗАДАЧА: Удалить остановленный контейнер

Вывод `docker rm crazy_tharp`\
![](./screenshots/2.10.png)

- ЗАДАЧА: Импортировать контейнер обратно через команду import

Вывод `docker import -c 'CMD ["nginx", "-g", "daemon off;"]' container.tar imported_nginx`\
![](./screenshots/2.11.png)

Вывод `docker images`\
![](./screenshots/2.12.png)

- ЗАДАЧА: Запустить импортированный контейнер

Вывод `docker run -d -p 80:80 -p 443:443 imported_nginx`\
![](./screenshots/2.13.png)

- ЗАДАЧА: Проверить, что по адресу localhost:80/status отдается страничка со статусом сервера nginx

Вывод localhost:80/status\
![](./screenshots/2.14.png)

## Part 3. Мини веб-сервер

- ЗАДАЧА: Написать мини-сервер на C и FastCgi, который будет возвращать простейшую страничку с надписью `Hello World!`

Вывод `cat server.c`\
![](./screenshots/3.1png)

- ЗАДАЧА: Запустить написанный мини-сервер через spawn-fcgi на порту 8080

Вывод `docker run -d -p 81:81 nginx`\
![](./screenshots/3.2png)

Вывод `docker cp nginx.conf sharp_yalow:/etc/nginx`\
![](./screenshots/3.3.png)

Вывод `docker cp server.c sharp_yalow:/home`\
![](./screenshots/3.4.png)

Вывод `docker exec -it sharp_yalow bash`\
![](./screenshots/3.5.png)

Вывод `apt-get update`\
![](./screenshots/3.6.png)

Вывод `apt-get install gcc spawn-fcgi libfcgi-dev`\
![](./screenshots/3.7.png)

Компилируем server.c командой: gcc server.c -lfcgi -o server

Вывод `spawn-fcgi -p 8080 ./server`\
![](./screenshots/3.8.png)

Вывод `nginx -s reload`\
![](./screenshots/3.9.png)

- ЗАДАЧА: Написать свой nginx.conf, который будет проксировать все запросы с 81 порта на 127.0.0.1:8080

Вывод `cat nginx.conf`\
![](./screenshots/3.11.png)

- ЗАДАЧА: Проверить, что в браузере по localhost:81 отдается написанная тобой страничка

Вывод localhost:81\
![](./screenshots/3.10.png)


## Part 4. Свой докер

При написании докер-образа избегай множественных вызовов команд RUN

- ЗАДАЧА: Написать свой докер-образ, который:
1) собирает исходники мини сервера на FastCgi из части 3;
2) запускает его на 8080 порту;
3) копирует внутрь образа написанный ./nginx/nginx.conf;
4) запускает nginx;

nginx можно установить внутрь докера самостоятельно, а можно воспользоваться готовым образом с nginx'ом, как базовым.

Вывод `cat Dockerfile`\
![](./screenshots/4.1.png)

Вывод `cat run.sh`\
![](./screenshots/4.2.png)


- ЗАДАЧА: Собрать написанный докер-образ через `docker build` при этом указав имя и тег

Вывод `docker build -t hypnosdu:1.0 .`\
![](./screenshots/4.3.png)

- ЗАДАЧА: Проверить через `docker images`, что все собралось корректно

Вывод `docker images`\
![](./screenshots/4.4.png)

- ЗАДАЧА: Запустить собранный докер-образ с маппингом 81 порта на 80 на локальной машине и маппингом папки ./nginx внутрь контейнера по адресу, где лежат конфигурационные файлы nginx'а (см. Часть 2)

Вывод `docker run -it --name hypnosdu-server -d -p 80:81 -v /Users/kirillzikevskiy/Desktop/S21/DO5_SimpleDocker-1/src/part_4/nginx.conf:/etc/nginx/nginx.conf hypnosdu:1.0`\
![](./screenshots/4.5.png)


- ЗАДАЧА: Проверить, что по localhost:80 доступна страничка написанного мини сервера

Вывод `curl localhost:80`\
![](./screenshots/4.6.png)

Вывод localhost:80\
![](./screenshots/4.7.png)


- ЗАДАЧА: Дописать в ./nginx/nginx.conf проксирование странички /status, по которой надо отдавать статус сервера nginx

Вывод `cat nginx.conf`\
![](./screenshots/4.8.png)

- ЗАДАЧА: Перезапустить докер-образ
*Если всё сделано верно, то, после сохранения файла и перезапуска контейнера, конфигурационный файл внутри докер-образа должен обновиться самостоятельно без лишних действий*

Вывод `docker restart hypnosdu-server`\
![](./screenshots/4.9.png)


- ЗАДАЧА: Проверить, что теперь по localhost:80/status отдается страничка со статусом nginx

Вывод localhost:80/status\
![](./screenshots/4.10.png)

Вывод `curl localhost:80/status`\
![](./screenshots/4.11.png)

## Part 5. Dockle

- Устанавливаем dockle. Для MacOS команда `brew install goodwithtech/r/dockle`

- ЗАДАЧА: Просканировать образ из предыдущего задания через `dockle [image_id|repository]`

Вывод `dockle hypnosdu:1.0`\
![](./screenshots/5.1.png)

- ЗАДАЧА: Исправить образ так, чтобы при проверке через dockle не было ошибок и предупреждений

Вывод `cat Dockerfile`\
![](./screenshots/5.2.png)

Вывод `dockle -ak NGINX_GPGKEY -ak NGINX_GPGKEY_PATH hypnosdu:1.0`\
![](./screenshots/5.3.png)

## Part 6. Базовый **Docker Compose**

- ЗАДАЧА: Написать файл docker-compose.yml, с помощью которого:
1) Поднять докер-контейнер из Части 5 (он должен работать в локальной сети, т.е. не нужно использовать инструкцию EXPOSE и мапить порты на локальную машину)
2) Поднять докер-контейнер с nginx, который будет проксировать все запросы с 8080 порта на 81 порт первого контейнера

Вывод `cat docker-compose.yml`\
![](./screenshots/6.1.png)


- ЗАДАЧА: Замапить 8080 порт второго контейнера на 80 порт локальной машины

Вывод `cat docker-compose.yml`\
![](./screenshots/6.2.png)


- ЗАДАЧА: Остановить все запущенные контейнеры

Выполняем `docker stop [CONTAINER]`

- ЗАДАЧА: Соберать и запустить проект с помощью команд `docker-compose build` и `docker-compose up`

Для того, чтобы контейнер с сервером из части 5 не останавливался после выполнения скрипта и продолжал работать, дописываем в скрипт run.sh из части 5 команду `while true; do sleep 1 done`

Вывод run.sh  из части 5\
![](./screenshots/6.7.png)

Вывод `docker-compose build`\
![](./screenshots/6.3.png)

Вывод `docker-compose up`\
![](./screenshots/6.4.png)


- ЗАДАЧА: Проверить, что в браузере по localhost:80 отдается написанная тобой страничка, как и ранее

Вывод localhost:80\
![](./screenshots/6.5.png)

Вывод `curl localhost:80`\
![](./screenshots/6.6.png)