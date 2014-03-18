var submit_http=null;
function call_submit(row)
{
	alert('hello')
	submit_ajax_init();
	var row_num='tr'+row;
	var rowId=document.getElementById(row_num);
	var devId=document.getElementById('devId_'+row_num);
	var timeId=document.getElementById('timeId_'+row_num);
	var selectId=document.getElementById('selectId_'+row_num);
	var switch_opt=get_select_text(selectId);
	var statId=document.getElementById('enableBoxId_'+row_num); 
	var enable_flg=(statId.checked==true)?'on':'off'
	var url="../cgi-bin/timer_sheet_submit.cgi?hub_id="+escape(row)+\
		 "&dev_name="+escape(devId.innerHTML)+\		
		 "&time="+escape(timeId.value)+\
		 "&switch_opt="+escape(switch_opt)+\
		 "&enableBox="+escape(enable_flg);
	document.write(url);
	submit_http.open("GET",url,true);
	submit_http.onreadystatechange=updateTimer;
	submit_http.send(null);
}
function updateTimer()
{
	if(submit_http.readyState == 4)
	{
		var ack=submit_http.responseText.split("&");	
		var sect=ack.split("|");
		var tr_num='tr'+sect[0];
		var dev_name=sect[1];
		var time=sect[2];
		var switch_opt=sect[3];
		var flag=sect[4];
		alert(ack);
		set_devname(tr_num,dev_name);
		switch_ctrl(tr_num,switch_opt);
		timer_enable(tr_num,flag);
		change_color(tr_num);
		set_timer(tr_num,time);

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
function get_select_text(selectId)
{
	var index=selectId.selectedIndex;
	var text=selectId.options[index].value;
	return text;
}
function submit_ajax_init()
{
	try  
	{  
			/* non-IE browser*/
			submit_http=new XMLHttpRequest();  
	}  
	catch (e)  
	{  
		try  
		{  
			submit_http=new ActiveXObject("Msxml2.XMLHTTP");
		}  
		catch (e)  
		{  
			submit_http=new ActiveXObject("Microsoft.XMLHTTP");  
		}  
	}
}
