#!/usr/bin/python
# -*- coding: utf-8 -*-

from selenium import webdriver
import time

from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities

driver = webdriver.Remote(command_executor='http://172.30.1.33:8910',desired_capabilities=DesiredCapabilities.PHANTOMJS)
f = open("/flag",'r')
flag = f.read()
f.close()

driver.get("http://password.gwht.io/login.php")
driver.find_element_by_name('username').send_keys("admin")
driver.find_element_by_name('password').send_keys(flag)
driver.find_element_by_name('remember').click()
data = driver.find_element_by_class_name('btn').click()
time.sleep(1)

driver.get("http://password.gwht.io/list.php")
lists = driver.find_elements_by_class_name('col-md-3')
lists.pop(0);
a = []
for li in lists:
	a.append(li.find_element_by_tag_name("a").get_attribute('href'))

for href in a:
	driver.get(href)
	time.sleep(1)
	
driver.quit()