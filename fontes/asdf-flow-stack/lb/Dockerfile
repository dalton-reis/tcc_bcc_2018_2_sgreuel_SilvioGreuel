FROM debian:latest as files

ADD traefik.toml /traefik.toml
ADD acme.json /acme.json

RUN chmod 600 /acme.json


FROM traefik:latest

LABEL maintainer="Silvio Greuel <silviogreuel@gmail.com>"
LABEL maintainer_name="Silvio Greuel"
LABEL maintainer_email="silviogreuel@gmail.com"

COPY --from=files /traefik.toml /traefik.toml
COPY --from=files acme.json /store/acme.json
