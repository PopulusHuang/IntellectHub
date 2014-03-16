var xmlHttp=null;
function table_submit(row_num)
{
	ajax_init();
	var rowId=document.getElementById(row_num);
	var devId=document.getElementById('devid_'+row_num);
	var timeId=document.getElementById('timeid_'+row_num);
	var selectId=document.getElementById('selectid_'+row_num);
	var switch_opt=get_select_text(selectId);
	var statId=document.getElementById('statid_'+row_num); 
	var url="../cgi-bin/timer_set.cgi?rowId="+escape(row_num)+\
		 "&dev_name="+escape(devId.innerHTML)+\		
		 "&time="+escape(timeId.value)+\
		 "&switch_opt="+escape(switch_opt)+\
		 "&timer_stat="+escape(statId.checked);
	xmlHttp.open("POST",url,true);
	xmlHttp.onreadystatechange=updateTimer;
	xmlHttp.send(null);
}
function updateTimer()
{
	if(xmlHttp.readyState == 4)
	{
		var ack=xmlHttp.responseText.split("&");	
	}
}
function get_select_text(selectId)
{
	var index=selectId.selectedIndex;
	var text=selectId.options[index].text;
	return text;
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
