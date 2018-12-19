FROM rabbitmq:3-management

LABEL maintainer="Silvio Greuel <silviogreuel@gmail.com>"
LABEL maintainer_name="Silvio Greuel"
LABEL maintaienr_email="silviogreuel@gmail.com"

RUN rabbitmq-plugins enable --offline \ 
	rabbitmq_tracing \
	rabbitmq_shovel \
	rabbitmq_shovel_management \
	rabbitmq_stomp \
	rabbitmq_web_stomp \
	rabbitmq_mqtt \
	rabbitmq_web_mqtt

ADD rabbitmq.conf /etc/rabbitmq/
ADD definitions.json /etc/rabbitmq/
