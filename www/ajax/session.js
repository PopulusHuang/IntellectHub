var session_request = null; 
function check_session()
{
	if(session_request == null)
		session_ajax_init();
	var session_id = getCookie("sesscli");
	var url = "../cgi-bin/check_session.cgi?session_id="+escape(session_id);
	session_request.open("GET",url,true);
	session_request.onreadystatechange=updatePage;
	session_request.send(null);
}
function updatePage()
{
	if(session_request.readyState == 4)	
	{
		var ack=session_request.responseText;
		if(ack != 'session_ok')
			location.href="../login.html";
	}
}
function getCookie(c_name)
{
if (document.cookie.length>0)
  {
  c_start=document.cookie.indexOf(c_name + "=")
  if (c_start!=-1)
    { 
    c_start=c_start + c_name.length+1 
    c_end=document.cookie.indexOf(";",c_start)
    if (c_end==-1) c_end=document.cookie.length
    return unescape(document.cookie.substring(c_start,c_end))
    } 
  }
return ""
}
function session_ajax_init()
{
	try  
	{  
		/* non-IE browser*/
		session_request = new XMLHttpRequest();  
	}  
	catch (e)  
	{  
		try  
		{  
			session_request = new ActiveXObject("Msxml2.XMLHTTP");
		}  
		catch (e)  
		{  
			session_request = new ActiveXObject("Microsoft.XMLHTTP");  
		}  
	}
}
