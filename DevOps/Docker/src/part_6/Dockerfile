FROM nginx
USER root
COPY ./nginx.conf /etc/nginx/nginx.conf
WORKDIR /home/
COPY ./run.sh .
ENTRYPOINT ["sh", "./run.sh"]
HEALTHCHECK NONE