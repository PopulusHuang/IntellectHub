var xmlHttp=null;
function call_server(bulbId)
{
	ajax_init();
	var id=document.getElementById(bulbId);
	var url="../cgi-bin/switch.cgi?name="+escape(id.name);
	xmlHttp.open("GET",url,true);
	xmlHttp.onreadystatechange=updateBulb;
	xmlHttp.send(null);
}
function updateBulb(){
	if(xmlHttp.readyState == 4)
	{
		var ack = xmlHttp.responseText.split(":");	
		var dev = document.getElementById("devhub1");
		if(ack[0] != null && ack[2] == "on")
		{
		img = document.getElementById(ack[0])
		img.src="../images/lighton.png";
		dev.innerHTML=ack[1];
		}
		else
		document.getElementById(ack[0]).src="../images/lightoff.png";
	}
}
function ajax_init()
{
	try  
	{  
			/* non-IE browser*/
			xmlHttp=new XMLHttpRequest();  
	}  
	catch (e)  
	{  
		try  
		{  
			xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");  
		}  
		catch (e)  
		{  
			xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");  
		}  
	}
}
