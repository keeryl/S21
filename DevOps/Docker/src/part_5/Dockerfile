FROM nginx
USER root
COPY ./nginx.conf /etc/nginx/nginx.conf
COPY ./server.c .
COPY ./run.sh .
RUN apt-get update && \
    apt-get install -y gcc spawn-fcgi libfcgi-dev && \
    rm -rf /var/lib/apt/lists
# WORKDIR /home/
ENTRYPOINT ["sh", "./run.sh"]
HEALTHCHECK NONE