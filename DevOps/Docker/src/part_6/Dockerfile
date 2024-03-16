FROM nginx
USER root
COPY ./nginx.conf /etc/nginx/nginx.conf
COPY ./run.sh .
# WORKDIR /home/
ENTRYPOINT ["sh", "./run.sh"]
HEALTHCHECK NONE