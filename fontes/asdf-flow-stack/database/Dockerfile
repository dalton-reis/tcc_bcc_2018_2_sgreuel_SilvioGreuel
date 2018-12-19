FROM postgres:latest

LABEL maintainer="Silvio Greuel <silviogreuel@gmail.com>"
LABEL maintainer_name="Silvio Greuel"
LABEL maintainer_email="silviogreuel@gmail.com"

ENV IOT_USER iot
ENV IOT_PASS iot
ENV IOT_DB iot

ADD ./init.sh /docker-entrypoint-initdb.d/init-user-db.sh
