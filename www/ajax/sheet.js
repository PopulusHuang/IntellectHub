var TAB_GLOBEL=true;	/*true:update Sheet;false:update row*/
var request_xmlHttp=null;
function call_submit(row,cgi_name)
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var row_num='tr'+row;
	var rowId=document.getElementById(row_num);
	var devId=document.getElementById('devId_'+row_num);
	var inputId=document.getElementById('inputId_'+row_num);
	var selectId=document.getElementById('selectId_'+row_num);
	var switch_opt=get_select_value(selectId);
	var statId=document.getElementById('enableBoxId_'+row_num); 
	var enable_flg=(statId.checked==true)?'on':'off';
	var url="../cgi-bin/"+cgi_name+".cgi?hub_id="+escape(row)+"&dev_name="+escape(devId.innerHTML)+"&inputVal="+escape(inputId.value)+"&switch_opt="+escape(switch_opt)+"&enableBox="+escape(enable_flg);
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updateSheet;
	request_xmlHttp.send(null);
	TAB_GLOBEL=false;
}
function call_sheet(cgi_name,tb_name)
{
	if(request_xmlHttp==null)
		request_ajax_init();
	var url="../cgi-bin/"+cgi_name+".cgi?tb_name="+escape(tb_name);
	request_xmlHttp.open("GET",url,true);
	request_xmlHttp.onreadystatechange=updateSheet;
	request_xmlHttp.send(null);
}
function updateSheet()
{
	if(request_xmlHttp.readyState==4)
	{
	  	var data=request_xmlHttp.responseText.split('&');	
		var sect=null;
		if(data==-1)
		{
			alert('提交更新失败!');	
		}
		else
		{
		for (var i = 0; i < data.length-1; i++) {
			sect = data[i].split('|');
			var tr_num='tr'+sect[0];	
			var dev_name=sect[1];
			var time=sect[2];
			var switch_opt=sect[3];
			var flag=sect[4];
			set_devname(tr_num,dev_name);
			switch_ctrl(tr_num,switch_opt);
			enable_box(tr_num,flag);
			change_color(tr_num);
			set_input(tr_num,time);
		}
		if(TAB_GLOBEL==false)/* update row data */
		{
			alert('提交更新成功!');
			TAB_GLOBEL=true;
		}
		}
	}
}
function set_devname(tr_num,dev_name)
{
	var devId=document.getElementById('devId_'+tr_num);	
	devId.innerHTML=dev_name;
}
function set_input(tr_num,time)
{
	var inputId=document.getElementById('inputId_'+tr_num);
	inputId.value=time;
}
function change_color(tr_num)
{
	row=document.getElementById(tr_num);
	boxrow=document.getElementById('enableBoxId_'+tr_num);
	inputId=document.getElementById('inputId_'+tr_num);
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
function enable_box(tr_num,flag)
{
	boxId=document.getElementById('enableBoxId_'+tr_num);
	value=(flag=='on')?1:null;
	boxId.checked=value;
}
function request_ajax_init()
{
	try  
	{  
			/* non-IE browser*/
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
function get_select_value(selectId)
{
	var index=selectId.selectedIndex;
	var value=selectId.options[index].value;
	return value;
}
