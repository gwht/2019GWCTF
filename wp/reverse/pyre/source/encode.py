#!/usr/bin/env python
# encoding: utf-8
# print "Welcome to Re World!"
# print "Your input1 is your flag~"
input1 = "GWHT{Just_Re_1s_Ha66y!}"
#input1 = "<?php public function index(){ echo 'Welcome to Hacker World ! ( you play CTF like cxk'; if (isset($_GET['z'])){$z = $_GET['z']; unserialize($z);}}"
code = ""
l = len(input1)
input1 = map(ord,input1)
for i in range(l):
	num = (((input1[i])+i) % 128 +128) % 128
	code += chr(num)
#print code
code = map(ord,code)
for i in range(l-1):
	code[i] = code[i]^code[i+1]
code = map(chr,code)
with open("Orz","wb") as f:
	for i in code:
		f.write(i)
#code = ['\x1f', '\x12', '\x1d', '(', '0', '4', '\x01', '\x06', '\x14', '4', ',', '\x1b', 'U', '?', 'o', '6', '*', ':', '\x01', 'D', ';', '%', '\x13']



