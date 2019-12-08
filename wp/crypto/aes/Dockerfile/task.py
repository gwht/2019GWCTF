# -*- coding:utf8 -*-
import SocketServer
import os
import random
import signal
import base64
from string import hexdigits
from hashlib import md5
from Crypto.Cipher import AES
from secret import flag, key

BS = 16

def pad(s):
    return s + (BS - len(s) % BS) * chr(BS - len(s) % BS)

def unpad(s):
    pad = s[-1]
    if ord(pad) > BS or ord(pad) < 1:
        raise ValueError("Invaild padding")
    for i in s[-ord(s[-1]):]:
        if ord(i) != ord(pad):
            raise ValueError("Invaild padding")
    res = s[0:-ord(s[-1])]
    return res

def encrypt(iv,data):
    mode = AES.MODE_CBC
    cipher = AES.new(key,mode,iv)
    ciphertext = cipher.encrypt(pad(data))
    return ciphertext

def decrypt(iv,data):
    mode = AES.MODE_CBC
    pt = AES.new(key,mode,iv)
    plaintext = pt.decrypt(data)
    return unpad(plaintext)

def get_secret():
    secret = encrypt("A" * 16, flag)
    return secret

class Task(SocketServer.BaseRequestHandler):
    def proof_of_work(self):
        random.seed(os.urandom(8))
        part_hash = "".join([random.choice(hexdigits) for _ in range(5)]).lower()
        salt = "".join([random.choice(hexdigits) for _ in range(4)]).lower()
        self.request.send("Please find a string that md5(str + " + salt + ")[0:5] == %s\n" % (part_hash))
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
        secret = base64.b64encode(get_secret())
        self.dosend('Welcome to this soEasy system.There are four options:\n')
        self.dosend('   [G] Get the secret message.\n')
        self.dosend('   [E] Encrypt the message.\n')
        self.dosend('   [D] Decrypt the message.\n')
        self.dosend('   [Q] Quit.\n')
        while True:
            self.dosend('[>] Please input your option: ')
            op = self.request.recv(10).strip().upper()
            if op == 'G':
                self.dosend('The secret is: ' + secret + '\n')
                continue
            elif op == 'E':
                self.dosend("[>] IV: ")
                ivv = self.request.recv(32)
                ivv = base64.b64decode(ivv.strip())
                self.dosend("[>] Data: ")
                data = self.request.recv(1024)
                data = base64.b64decode(data.strip())
                try:
                    cipher = base64.b64encode(encrypt(ivv, data))
                except Exception,e:
                    self.dosend("[-] %s\n" % e)
                    continue
                else:
                    self.dosend("The result is: %s\n" % cipher)
                    self.dosend("Encrytion done\n")
                    continue
            elif op == 'D':
                self.dosend("[>] IV: ")
                cv = self.request.recv(32)
                cv = base64.b64decode(cv.strip())
                self.dosend("[>] Data: ")
                cdata = self.request.recv(1024)
                cdata = base64.b64decode(cdata.strip())
                try:
                    decrypt(cv, cdata)
                except Exception,e:
                    self.dosend("[-] %s\n" % e)
                    continue
                else:
                    self.dosend("Decrpytion done\n")
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


