FROM ubuntu

RUN apt-get update && apt-get -y install python-dev && apt-get -y install python-pip && apt-get -y install vim && && apt-get -y install libgmp-dev && apt-get -y install libmpfr-dev && apt-get -y install libmpc-dev

RUN pip install gmpy2

ADD run.sh /root/run.sh

RUN chmod +x /root/run.sh

RUN useradd -m -s /sbin/nologin dsa

ADD secret.py /home/dsa/secret.py

ADD task.py /home/dsa/task.py

EXPOSE 80
CMD ["/root/run.sh"]