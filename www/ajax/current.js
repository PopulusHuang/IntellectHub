var request_xmlHttp=null;
/* call list user information */
function call_currMQ2()
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var url="../cgi-bin/curr_MQ2.cgi";	
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updateCurrMQ2;
	request_xmlHttp.send(null);
}
function updateCurrMQ2()
{
	if(request_xmlHttp.readyState==4)
	{
  		var ack=request_xmlHttp.responseText;	
		var data=ack.split(":");
		var currMQ2 = document.getElementById('currMQ2');
		var currTemp = document.getElementById('currTemp');
		var currdata=parseInt(data[0]);
		var valve = parseInt(data[1]);
		if(currdata > valve)
		{
			alert('烟雾警报!');	
		//	alert(data);
		}
		currMQ2.innerHTML=data[0];
		currTemp.innerHTML=data[2];
	}
}
function request_ajax_init()
{
	try  
	{  
			request_xmlHttp=new XMLHttpRequest();  
	}  
	catch (e)  
	{  
		try  
		{  
			request_xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
		}  
		catch (e)  
		{  
			request_xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");  
		}  
	}
}
