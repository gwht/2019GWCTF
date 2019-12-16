FROM ubuntu:latest

RUN apt-get update
RUN apt-get install cron && \
	apt-get install python3 -y && \
	apt-get install python3-pip -y
RUN pip3 install selenium==2.48.0

COPY bot.py /
COPY flag /
COPY crontabfile /
COPY run.sh /

RUN crontab /crontabfile
RUN apt-get -y install rsyslog
RUN cp /crontabfile /etc/crontab
RUN touch /var/log/cron.log
RUN chmod +x /run.sh

CMD ["bash","/run.sh"]