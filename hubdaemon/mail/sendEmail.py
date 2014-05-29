#!/usr/bin/python
#-*- coding: utf-8 -*-
import smtplib
import os
import sqlite3
def getMQ2():
	MQ2=os.popen('./get_MQ2').read()
def getRecvEmail():

def sendEmail(receiver):
	server= 'smtp.sina.com'
	
	sender = 'notdoevil@sina.cn'
	password='Notdoevilsina'
	receiver = 'littleismore@sina.com'
	subject = 'Greeting from pcDuino'
	body = 'Welcome to pcDuino!mypasswd:Notdoevilsina'
	
	"Sends an e-mail to the specified receiver."
	
	body = "" + body + ""
	
	headers = ["From: " + sender,
			"Subject: " + subject,
			"To: " + receiver,
			"MIME-Version: 1.0",
			"Content-Type: text/html"]
	headers = "\r\n".join(headers)
	
	session = smtplib.SMTP(server)
	
	session.ehlo()
	session.starttls()
	session.ehlo
	session.login(sender, password)
	
	session.sendmail(sender, receiver, headers + "\r\n\r\n" + body)
	session.quit()
