var xmlHttp=null;
function call_server(bulbId)
{
	ajax_init();
	var id=document.getElementById(bulbId);
	var switch_stat=null;
	if(id.src.match("bulbon") != null)
		switch_stat="on";
	if(id.src.match("bulboff") != null)
		switch_stat="off";
	var url="../cgi-bin/switch.cgi?name="+escape(id.name)+"&status="+escape(switch_stat);
	xmlHttp.open("GET",url,true);
	xmlHttp.onreadystatechange=updateBulb;
	xmlHttp.send(null);
}
function updateBulb(){
	if(xmlHttp.readyState == 4)
	{
		var ack = xmlHttp.responseText.split(":");	
		if(ack[0] != null )
		{
		var dev = document.getElementById("dev"+ack[0]);
		if(dev.innerHTML != ack[1])
			dev.innerHTML=ack[1];
		img = document.getElementById(ack[0])
		img.src="../images/bulb"+ack[2]+".png";
		}
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
