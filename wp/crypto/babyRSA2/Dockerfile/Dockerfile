FROM ubuntu

RUN apt-get update && apt-get -y install python-dev && apt-get -y install python-pip && apt-get -y install vim 

ADD run.sh /root/run.sh

RUN chmod +x /root/run.sh

RUN useradd -m -s /sbin/nologin ctf

ADD secret.py /home/ctf/secret.py

ADD task.py /home/ctf/task.py

EXPOSE 80
CMD ["/root/run.sh"]