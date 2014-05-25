import poplib  

from email import parser  

host = 'pop.sina.com'  

username = 'littleismore@sina.com'  

password = '2014thinkdiff'  

pop_conn = poplib.POP3_SSL(host)  

pop_conn.user(username)  

pop_conn.pass_(password)  

#Get messages from server:  

Messages = [pop_conn.retr(i) for i in range(1,len(pop_conn.list()[1]) + 1)]  

# Concat message pieces:  

messages = ["\n".join(mssg[1]) for mssg in Messages]  

#Parse message intom an email object:  

messages = [parser.Parser().parsestr(mssg) for mssg in messages]  

for message in messages:  
	print message['From']  
	print message['To'] 
	print message['Subject'] 
pop_conn.quit()  
