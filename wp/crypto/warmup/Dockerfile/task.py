# -*- coding:utf8 -*-
import SocketServer
import os
import random
import signal
from hashlib import sha512
from string import hexdigits
from hashlib import md5
from secret import flag, x

p = 31198248455472731019496739215340201911997057848114316587736933789227647718169482560810230958070804578189477351219382835524617763638444679674283860732694106535921123709020157143505759378845493643543645485243621585916026567257758724686390209844774364090557106863570579284085225367749748548340935277073521514074799620283516155381243321074955880189777530837366464771336121525352256584638514044946007673213774688190611880253588873492853744482951036316464773140620933329882218152102453349630470887781081977786889788859346884287040811643781888419852158190238918746840727700831299776696567343878267453273493961712386563291619
q = 20948050262666044906815614916146712099544774622841631794787589234359
g = 9947348980181878795045460021432558061459250728913897956997945102590350886740171571394791330584892632995503165439387886413900153587642528239561098327038430382486510419238271146265963157969008284265413784141362375985358337770707337939487121706384789363706759097209047466500616322805911811795907273855531866406327411008809923706430048352935822122291410673205412066593837036378348795368045763181748208191525066037090863027437381039691077876004532006957843442561322685709769494933660667617310844425949999387793016131076676066319826896398049265758607043258466448433981209961716741242954311079090246525605491939426268727276

def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return x % m

def s2h(s):
    return ''.join([hex(ord(c)).replace('0x', '') for c in s])

def h2i(s):
    return int(str(s),16)

def nonce(msg, num):
    n = 0
    msg = h2i(msg)
    j = len(str(num))
    for i in str(msg):
        i = int(i) ** int(i) * j
        d = int(str(int(i) * 987654321)[-6:])
        n += num % d
    n = (num - n**2) % d
    return n

def sign(data):
    data = s2h(data)
    k = nonce(data,q)
    kinv = modinv(k,q)
    r = pow(g, k, p) % q
    h = sha512(data).hexdigest()
    h = int(h, 16)
    s = kinv * (h + r * x) % q
    return (r,int(s))

def admin_auth():
    username = "admin"
    return sign(username)

class Task(SocketServer.BaseRequestHandler):
    def proof_of_work(self):
        random.seed(os.urandom(8))
        part_hash = "".join([random.choice(hexdigits) for _ in range(5)]).lower()
        salt = "".join([random.choice(hexdigits) for _ in range(4)]).lower()
        self.request.send("[*] Please find a string that md5(str + " + salt + ")[0:5] == %s\n" % (part_hash))
        self.request.send('[>] Give me xxxxx: ')
        string = self.request.recv(10)
        string = string.strip()
        if (md5(string + salt).hexdigest()[:5] != part_hash):
            self.request.send('[-] Wrong hash, exit...\n')
            return False
        return True

    def dosend(self, msg):
        try:
            self.request.sendall(msg)
        except:
            pass

    def handle(self):
        signal.alarm(500)
        if not self.proof_of_work():
            return
        signal.alarm(450)

        self.dosend('[*] Welcome to this sososoEasy system.Only admin can see the flag.\n')
        self.dosend('    [1] Login.\n')
        self.dosend('    [2] Administrator verification.\n')
        self.dosend('    [3] Quit.\n')
        while True:
            self.dosend('[>] Please input your option: ')
            op = self.request.recv(5).strip().upper()
            if op == '1':
                self.dosend('Input your username:\n')
                self.dosend('[>] ')
                username = self.request.recv(1024).strip()
                if username == "admin":
                    self.dosend("You're not admin.\n")
                else:
                    signature = sign(username)
                    signature = '(' + repr(signature[0]) + "," + repr(signature[1]) + ")"
                    self.dosend('Welcome %s!\n' % username)
                    self.dosend('This is your signature: %s\n' % signature)
                continue
            elif op == '2':
                self.dosend("Please input the administrator's signature:\n")
                self.dosend('[>] ')
                res = self.request.recv(1024).strip()
                res = res.replace(" ", "")
                res = res[1:-1].replace("L", "").split(",", 1)
                admin_sign = admin_auth()
                getflag = 0
                for x, y in zip(res, admin_sign):
                    if long(x) != y:
                        getflag = 0
                    else:
                        getflag += 1
                if getflag == 2:
                    self.dosend("Welcome admin!\n")
                    self.dosend("The flag is %s\n" % flag)
                    return False
                else:
                    self.dosend("OMG!～You lied to me.\n")
                    continue
            else:
                self.dosend("GoodBye~\n")
                return False
        self.request.close()

class ForkedServer(SocketServer.ForkingTCPServer, SocketServer.TCPServer):
    pass


if __name__ == '__main__':
    HOST, PORT = '0.0.0.0', 80
    server = ForkedServer((HOST, PORT), Task)
    server.allow_reuse_address = True
    server.serve_forever()