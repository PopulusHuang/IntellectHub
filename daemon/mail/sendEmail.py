#!/usr/bin/python
#-*- coding: utf-8 -*-
import smtplib

server= 'smtp.sina.com'

sender = 'littleismore@sina.com'
password='2014thinkdiff'
recipient = 'notdoevil@sina.cn'
subject = 'Greeting from pcDuino'
body = 'Welcome to pcDuino!mypasswd:2014thinkdiff '

"Sends an e-mail to the specified recipient."

body = "" + body + ""

headers = ["From: " + sender,
		"Subject: " + subject,
		"To: " + recipient,
		"MIME-Version: 1.0",
		"Content-Type: text/html"]
headers = "\r\n".join(headers)

session = smtplib.SMTP(server)

session.ehlo()
session.starttls()
session.ehlo
session.login(sender, password)

session.sendmail(sender, recipient, headers + "\r\n\r\n" + body)
session.quit()
