FROM ubuntu

RUN apt-get update && apt-get -y install python-dev && apt-get -y install python-pip && apt-get -y install vim

ADD run.sh /root/run.sh

RUN chmod +x /root/run.sh

RUN useradd -m -s /sbin/nologin aes

ADD secret.py /home/aes/secret.py

ADD task.py /home/aes/task.py

EXPOSE 80
CMD ["/root/run.sh"]