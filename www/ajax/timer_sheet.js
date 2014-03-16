var timer_xmlHttp=null;
function call_sheet()
{
	timer_ajax_init()
	var url="../cgi-bin/timer_sheet_show.cgi"
	timer_xmlHttp.open("POST",url,true);
	timer_xmlHttp.onreadystatechange=updateSheet;
	timer_xmlHttp.send(null);
}
function updateSheet()
{
	if(timer_xmlHttp.readyState==4)
	{
		var tableId=document.getElementById('timer_tb');
	  	var data=timer_xmlHttp.responseText.split('&');	
		var sect=null;
		for (var i = 0; i < data.length-1; i++) {
			sect = data[i].split('|');	
			var tr_num='tr'+sect[0];	
			var dev_name=sect[1];
			var time=sect[2];
			var switch_opt=sect[3];
			var flag=sect[4];
			set_devname(tr_num,dev_name);
			switch_ctrl(tr_num,switch_opt);
			timer_enable(tr_num,flag);
			change_color(tr_num);
			set_timer(tr_num,time);
		}
	}
}
function set_devname(tr_num,dev_name)
{
	var devId=document.getElementById('devId_'+tr_num);	
	devId.innerHTML=dev_name;
}
function set_timer(tr_num,time)
{
	var timeId=document.getElementById('timeId_'+tr_num);
	timeId.value=time;
}
function change_color(tr_num)
{
	row=document.getElementById(tr_num);
	boxrow=document.getElementById('enableBoxId_'+tr_num);
	inputId=document.getElementById('timeId_'+tr_num);
	selectId=document.getElementById('selectId_'+tr_num);

	if(boxrow.checked==true)
	{
		row.style.color='green';
		boxrow.style.color='green';
		inputId.style.color='green';
		selectId.style.color='green';

	}
	else
	{
		row.style.color='gray';
		boxrow.style.color='gray';
		inputId.style.color='gray';
		selectId.style.color='gray';
	}
}
function switch_ctrl(tr_num,stat)
{
	selectId=document.getElementById('selectId_'+tr_num);	
	selectId.options[stat].selected=true;
}
function timer_enable(tr_num,flag)
{
	boxId=document.getElementById('enableBoxId_'+tr_num);
	value=(flag=='on')?1:null;
	boxId.checked=value;
}
function timer_ajax_init()
{
	try  
	{  
			/* non-IE browser*/
			timer_xmlHttp=new XMLHttpRequest();  
	}  
	catch (e)  
	{  
		try  
		{  
			timer_xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
		}  
		catch (e)  
		{  
			timer_xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");  
		}  
	}
}
